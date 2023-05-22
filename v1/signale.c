#include <setjmp.h>
#include <signal.h>
#include "hdr.h"

static void sig_alarm();

int main(void)
{
    int n;
    if (signal(SIGALRM, sig_alarm) == SIG_ERR)
        err_sys("eroare signal");

    alarm(10);
    sleep(20);
    alarm(0);
    printf("main1: x = 2; \n"); // primul

    fork();
    printf("main2: x = 2; "); // unul pentru fiecare proces
    fork();
    //alarm(1);
    //pause();
    wait(&n);
    exit(0);
}

static void sig_alarm(int sig)
{
    printf("sigalarm: x = 2 \n"); // al doilea
    return;
}
