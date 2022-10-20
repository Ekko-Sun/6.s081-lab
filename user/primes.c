#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>

void sieve(int pleft[2])
{
    int p;
    read(pleft[0], &p, sizeof(p));
    if (p == -1) //表示已经处理完数字
    {
        exit(0);
    }
    printf("prime %d\n", p);

    int pright[2];
    pipe(pright);

    if (fork() == 0) //子进程
    {
        close(pright[1]);
        close(pleft[0]);
        sieve(pright);
    }
    else
    {
        //父进程
        close(pright[0]);
        int buf;
        while (read(pleft[0], &buf, sizeof(buf)) && buf != -1)
        {
            if (buf % p != 0)
            {
                write(pright[1], &buf, sizeof(buf));
            }
        }
        buf = -1;
        write(pright[1], &buf, sizeof(buf));
        wait(0); //等待子进程
    }
    exit(0);
}
int main()
{
    // 主进程
    int input_pipe[2];
    pipe(input_pipe); //声明输入的管道，输入2到35之间的数字。

    if (fork() == 0)
    {
        //第一个stage的子进程
        close(input_pipe[1]); //子进程只需要读管道，关闭管道的写描述符。
        sieve(input_pipe);
    }
    else
    {
        // 主进程
        close(input_pipe[0]); //主进程只需要写管道，关闭管道的读文件描述符。
        int i;
        for (i = 2; i <= 35; i++)
        {
            write(input_pipe[1], &i, sizeof(i));
        }
        i = -1;
        write(input_pipe[1], &i, sizeof(i));
        wait(0);
    }
    exit(0);
}