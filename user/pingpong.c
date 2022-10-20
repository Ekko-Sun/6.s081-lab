#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>

int main(int argc, char **argv)
{
    int sender[2], receiver[2];
    pipe(sender);
    pipe(receiver);
    if (fork() != 0)
    {
        write(sender[1], "!", 1);
        char buf;
        read(receiver[0], &buf, 1);
        printf("%d received pong\n", getpid());
        wait(0);
    }
    else
    {
        char buf;
        read(sender[0], &buf, 1);
        printf("%d received ping\n", getpid());
        write(receiver[1], &buf, 1);
    }
    exit(0);
}