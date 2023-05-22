#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define SEMPERM 0600

int initsem(key_t semkey)
{
    int status, semid;
    semid = semget(semkey, 1, SEMPERM | IPC_CREAT);
    status = semctl(semid, 0, SETVAL, 0);
    return semid;
}

int p(int semid)
{
    struct sembuf pbuf;
    pbuf.sem_num = 0;
    pbuf.sem_op = -1;
    pbuf.sem_flg = SEM_UNDO;
    semop(semid, &pbuf, 1);
    return 0;
}

int v(int semid)
{
    struct sembuf vbuf;
    vbuf.sem_num = 0;
    vbuf.sem_op = 1;
    vbuf.sem_flg = SEM_UNDO;
    semop(semid, &vbuf, 1);
    return 0;
}

int main(void)
{
    key_t semkey = 0x200;
    int semid, x = 0;
    semid = initsem(semkey);

    // fork returneaza 0 in procesul copil
    // fork returneaza pid-ul copilului in procesul parinte

    if (fork() == 0)
    {
        p(semid);
        x += 1;
        return x;
    }

    if (fork() == 0)
    {
        x += 2;
        v(semid);
        return x;
    }

    printf("x = %d", x);
    return x;
}
