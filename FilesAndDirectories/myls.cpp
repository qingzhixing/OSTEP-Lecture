#include <iostream>
#include <sys/stat.h>
#include <sys/dir.h>
#include <string>
#include <getopt.h>

using std::cout;
using std::endl;
using std::string;

bool long_format = false;

void print_usage(const string &prog_name)
{
	cout << "Usage: " << prog_name << " [-l] [Directory]" << endl;
	cout << "Options:" << endl;
	cout << "  -l  Long format" << endl;
	cout << "  -h --help  Show this help message" << endl;
	cout << "!!!Max Directory count: Only ONE!!!" << endl;
	cout << "If no path is specified, the current directory is used." << endl;
}

void handle_file(const string &file_path)
{
	string file_name = file_path.substr(file_path.find_last_of("/") + 1);
	struct stat buf;
	if (stat(file_path.c_str(), &buf) == -1)
	{
		perror("stat");
		return;
	}

	if (S_ISDIR(buf.st_mode))
	{
		return;
	}

	if (long_format)
	{

		// 打印文件所有者，所属组权限以及stat信息
		cout << "[" << file_name << "]" << endl;
		cout << "Owner: " << buf.st_uid << endl;
		cout << "Group: " << buf.st_gid << endl;
		cout << "Permissions: " << (buf.st_mode & 0777) << endl;
		cout << "Size: " << buf.st_size << endl;
		cout << "Inode: " << buf.st_ino << endl;
		cout << "Blocks: " << buf.st_blocks << endl;
		cout << "Last accessed: " << buf.st_atime << endl;
		cout << "Last modified: " << buf.st_mtime << endl;
		cout << "Last changed: " << buf.st_ctime << endl;
		cout << endl;
	}
	else
	{
		cout << file_name << endl;
	}
}

int main(int argc, char *const *argv)
{
	// 定义长选项
	static struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0},
	};

	// get -l and -h option
	int opt;
	int option_index = 0;
	while ((opt = getopt_long(argc, argv, "lh", long_options, &option_index)) != -1)
	{
		switch (opt)
		{
		case 'l':
			long_format = true;
			break;
		case 'h':
			print_usage(argv[0]);
			exit(0);
		default:
			print_usage(argv[0]);
			exit(1);
		}
	}

	struct stat buf;
	string real_path = "./";

	// 判断后面还有没有参数
	if (optind < argc - 1)
	{
		// 判断后面参数是否只有一个
		if (optind != argc - 1)
		{
			print_usage(argv[0]);
			return 1;
		}
		real_path = argv[optind];
	}
	else
	{
		real_path = "./";
	}

	// 判断是否存在
	if (stat(real_path.c_str(), &buf) == -1)
	{
		perror("stat");
		return 1;
	}

	// 判断是否是目录
	bool is_dir = S_ISDIR(buf.st_mode);
	if (!is_dir)
	{
		print_usage(argv[0]);
		return 1;
	}

	// 处理目录
	auto dir = opendir(real_path.c_str());
	if (dir == nullptr)
	{
		perror("opendir");
		return 1;
	}

	// 读取目录
	struct dirent *entry;
	while ((entry = readdir(dir)) != nullptr)
	{
		auto file_path = real_path + "/" + entry->d_name;
		handle_file(file_path);
	}

	return 0;
}