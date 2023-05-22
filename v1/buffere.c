#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int x = 6;
    char msg2[] = "123";
    int n=0;
    int pfd[2], pid;
    pipe(pfd);
    if((pid=fork()) == 0) {
        x = 2;
        n = read(pfd[0], msg2, 5);
        x -= 1;
        printf("x = %d\n", x);
        exit(0);
    }
    else {
        x = 4;
        n = write(pfd[1], msg2, 5);
    }
}