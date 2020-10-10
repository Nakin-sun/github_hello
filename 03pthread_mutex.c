#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMMAX      20
#define BUFSIZE     1024
pthread_mutex_t mutex;
void *myfunc(void *p)
{
	FILE *fp;
	char buf[BUFSIZE];
	fp = fopen("./a.text","r+");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}
	pthread_mutex_lock(&mutex);
	fgets(buf,BUFSIZE,fp);

	fseek(fp,0,SEEK_SET);
	fprintf(fp,"%d\n",atoi(buf)+1);
	fclose(fp);
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
	pthread_t tid[NUMMAX];
	
	int i=0,err;
	pthread_mutex_init(&mutex,NULL);
	for(i = 0;i < NUMMAX;i++)
	{
		err = pthread_create(tid+i,NULL,myfunc,NULL);
		if(err)
		{
			fprintf(stderr,"pthread_create():%s\n",strerror(err));
			exit(1);
		}
	}
	for(i = 0;i < NUMMAX;i++)
	{
		pthread_join(tid[i]);
	}
	pthread_mutex_destroy(&mutex);
	return 0;
}
