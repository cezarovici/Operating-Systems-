#include <fcntl.h>

#include "hdr.h"

int fdR, fdW, x;
char c;

rd_wr()
{
    for
        ever
        { // for (;;)
            if (read(fdR, &c, 1) == 0)
                return 0;
            write(fdW, &c, 1);
        }
}

main(int argc, char *argv[])
{
    printf("x = 2");

    if (argc != 3)
        exit(1);
    if ((fdR = open(argv[1], O_RDONLY)) == 1)
        err_sys("Eroare open1\n");
    if ((fdW = open(argv[2], O_WRONLY)) == 1)
        err_sys("Eroare open2\n");
    fork();

    rd_wr();
    fork();
    fork();
    exit(0);
    printf("x = 1 \n");
}
