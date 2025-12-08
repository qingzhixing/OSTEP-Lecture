#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <cerrno>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <File/Directory Path>" << endl;
		return 1;
	}

	// 判断文件/目录是否存在
	struct stat buf;
	// 调用stat函数判断文件/目录是否存在
	if (stat(argv[1], &buf) == -1)
	{
		cout << "Error: " << strerror(errno) << endl;
		return 1;
	}

	string call_name{};

	// 判断是否为目录
	if (S_ISDIR(buf.st_mode))
	{
		call_name = "Directory";
	}
	else
	{
		call_name = "File";
	}

	// 输出文件/目录类型
	cout << argv[1] << " is a " << call_name << "." << endl;

	// 目标大小
	cout << call_name << " Size: " << buf.st_size << " Bytes." << endl;

	// 分配的磁盘块数
	cout << call_name << " Blocks: " << buf.st_blocks << endl;

	// 引用计数
	cout << call_name << " Links: " << buf.st_nlink << endl;

	return 0;
}