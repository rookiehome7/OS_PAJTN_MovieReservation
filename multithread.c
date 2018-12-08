#include <stdio.h>
#include <assert.h>
#include <pthread.h>

static volatile int counter = 0;


// gcc -Wall -Ipthread -o multithread multithread.c

void *mythread(void *arg)
{
	int i;
	for (i=0;i<1000000;i++){
		counter = counter + 1;
	}
	printf("%s: done\n", (char*) arg);
	return NULL;
}


int main (int argc,char *argv[])
{
	pthread_t p1,p2;
	printf("Before Counter %d\n",counter);
	pthread_create(&p1,NULL,mythread,"A");
	pthread_create(&p2,NULL,mythread,"B");

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	printf("After Counter %d\n",counter);
	return 0;

}