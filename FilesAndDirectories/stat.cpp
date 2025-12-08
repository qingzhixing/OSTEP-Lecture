#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <cerrno>
#include <string>
#include <vector>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

// 检查路径是否为绝对路径
bool is_absolute_path(const string &path)
{
	return !path.empty() && path[0] == '/';
}

// 检查路径是否为相对路径
bool is_relative_path(const string &path)
{
	return !path.empty() && path[0] != '/';
}

// 从PATH环境变量中查找文件
string find_in_path(const string &filename)
{
	char *path_env = getenv("PATH");
	if (!path_env)
	{
		return "";
	}

	std::stringstream ss(path_env);
	string dir;

	while (std::getline(ss, dir, ':'))
	{
		string full_path = dir + "/" + filename;
		struct stat buf;
		if (stat(full_path.c_str(), &buf) == 0)
		{
			return full_path;
		}
	}

	return "";
}

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <File/Directory Path>" << endl;
		return 1;
	}

	string input_path = argv[1];
	string actual_path = input_path;

	// 判断文件/目录是否存在
	struct stat buf;

	// 如果是相对路径，尝试从PATH环境变量查找
	if (is_relative_path(input_path) && input_path.find('/') == string::npos)
	{
		string found_path = find_in_path(input_path);
		if (!found_path.empty())
		{
			actual_path = found_path;
			cout << "Found in PATH: " << found_path << endl;
		}
	}

	// 调用stat函数判断文件/目录是否存在
	if (stat(actual_path.c_str(), &buf) == -1)
	{
		char *error = strerror(errno);
		cout << "Error: " << error << endl;

		// 如果是相对路径且不在当前目录，提示用户
		if (is_relative_path(input_path) && input_path.find('/') != string::npos)
		{
			cout << "Note: This is a relative path. Please provide absolute path or check the file location." << endl;
		}
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

	// 目标大小
	cout << call_name << " Size: " << buf.st_size << " Bytes." << endl;

	// 分配的磁盘块数
	cout << call_name << " Blocks: " << buf.st_blocks << endl;

	// 引用计数
	cout << call_name << " Links: " << buf.st_nlink << endl;

	return 0;
}