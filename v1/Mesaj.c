/******************** MESAJ.C ********************/
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include "hdr.h"

#define MAXOPEN 20 /* nr. cozi mesaje deschise */
#define MAXMSG 4 /* nr. max. de mesaje */
typedef enum { FALSE, TRUE} BOOLEAN;

struct msgbuf{
    long    mtype;
    char    mtext[256];
};
 

static int openqueue( int key)
{
	static struct { /* inf. despre mesaj */
		int key; /* cheia fisierului */
		int qid; /* descriptorul asociat cozii */
	} queues[ MAXOPEN];
	int i, avail, qid;
	avail = -1; /* nu s-a gasit descriptor valabil */
	for( i=0; i < MAXOPEN; i++) { /* poate e deschis deja */
		if( queues[i].key == key) /* s-a gasit */
			return( queues[i].qid);
		if( queues[i].key == 0 && avail == -1 )
			avail = i;
	}
	if( avail == -1 ) {
		errno = 0;
		return(-1);
	}
	if( (qid=msgget(key, 0666 | IPC_CREAT)) < 0)
		return(-1);
	queues[ avail].key = key;
	queues[ avail].qid = qid;
	return qid;
}

BOOLEAN send( int dstkey, struct msgbuf *buf, int nbytes)
{
	int qid;
	if( (qid = openqueue( dstkey)) < 0) {
		fprintf( stderr, "Send - Eroare openqueue\n");
		return FALSE;
	}
	buf->mtype=1;
	return( msgsnd(qid,buf,nbytes-sizeof(buf->mtype),0) != -1);
}

BOOLEAN receive( int srckey, struct msgbuf *buf, int nbytes)
{
	int qid;
	if( ( qid = openqueue( srckey)) < 0) {
		fprintf( stderr, "Receive - Eroare openqueue\n");
		return FALSE;
	}
	return(msgrcv(qid,buf,nbytes-sizeof(buf->mtype),0L,0) !=-1);
}
void rmqueue( int key)
{
	int qid;
	if( ( qid=openqueue( key)) < 0 ||msgctl( qid, IPC_RMID, NULL) < 0)
		err_sys("Eroare rmqueue");
}

