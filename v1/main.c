#include <stdio.h>

int main(void) {
    printf("x ");
    int pid = fork();
    if(pid == 0) {
        printf("y");
    }
    
    return 0;
}