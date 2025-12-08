#include <iostream>
#include <sys/stat.h>
#include <getopt.h>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

using std::cout;
using std::endl;
using std::string;

// 找到倒数第n行的起始位置
off_t find_nth_line_from_end(int fd, int n)
{
	struct stat file_stat;
	if (fstat(fd, &file_stat) == -1)
	{
		perror("fstat");
		return -1;
	}

	off_t file_size = file_stat.st_size;
	if (file_size == 0)
	{
		return 0; // 空文件
	}

	// 从文件末尾开始反向查找换行符
	off_t pos = file_size - 1;
	int line_count = 0;
	char ch;

	// 反向查找换行符
	while (pos >= 0 && line_count < n)
	{
		lseek(fd, pos, SEEK_SET);
		if (read(fd, &ch, 1) == 1)
		{
			if (ch == '\n')
			{
				line_count++;
				// 找到倒数第n行的换行符位置
				if (line_count == n)
				{
					return pos + 1; // 换行符后的位置
				}
			}
		}
		pos--;
	}

	// 如果找到文件开头但行数不足，返回文件开头
	return (pos < 0) ? 0 : pos + 1;
}

int main(int argc, char *const *argv)
{
	// 解析命令行参数
	int opt;
	int num_lines = 10;
	while ((opt = getopt(argc, argv, "n:")) != -1)
	{
		switch (opt)
		{
		case 'n':
			num_lines = std::stoi(optarg);
			break;
		default:
			cout << "Usage: " << argv[0] << " [-n num_lines] file" << endl;
			return 1;
		}
	}

	// 检查是否有文件参数
	if (optind >= argc)
	{
		cout << "Usage: " << argv[0] << " [-n num_lines] file" << endl;
		return 1;
	}

	string filename = argv[optind];

	// 打开文件
	int fd = open(filename.c_str(), O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return 1;
	}

	// 找到倒数第num_lines行的起始位置
	off_t start_pos = find_nth_line_from_end(fd, num_lines);
	if (start_pos == -1)
	{
		close(fd);
		return 1;
	}

	// 跳转到计算出的位置
	lseek(fd, start_pos, SEEK_SET);

	// 读取文件内容
	char buffer[1024];
	ssize_t bytes_read;
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
	{
		write(STDOUT_FILENO, buffer, bytes_read);
	}

	// 关闭文件描述符
	close(fd);

	return 0;
}