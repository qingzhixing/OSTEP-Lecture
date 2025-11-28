
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

int main()
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 创建第一个子进程（生产者）
    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        // 关闭管道的读端
        close(pipefd[0]);

        // 将标准输出重定向到管道的写端
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // 执行第一个命令（例如：生成数据的程序）
        execlp("ls", "ls", "-l", nullptr); // 示例命令
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // 创建第二个子进程（消费者）
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        // 关闭管道的写端
        close(pipefd[1]);

        // 将标准输入重定向到管道的读端
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        // 执行第二个命令（例如：处理数据的程序）
        execlp("wc", "wc", "-l", nullptr); // 示例命令
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // 父进程关闭管道两端
    close(pipefd[0]);
    close(pipefd[1]);

    // 等待两个子进程结束
    waitpid(pid1, nullptr, 0);
    waitpid(pid2, nullptr, 0);

    return 0;
}