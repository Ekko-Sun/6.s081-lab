#include <kernel/types.h>
#include <kernel/stat.h>
#include <kernel/fcntl.h>
#include <user/user.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("err! command should be sleep <ticks>\n");
    }
    int ticks = atoi(argv[1]);
    sleep(ticks);
    exit(0);
}