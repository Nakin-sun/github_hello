#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct mynum
{
	int num;
};
void *myfunc(void *arg);
int main(int argc, const char *argv[])
{
	int i=0;
	int err;
	void *ptr = NULL;
	struct mynum *stp = NULL;
	pthread_t tid[100];
	for(i = 100;i < 200;i++ )
	{
		stp = (struct mynum *)malloc(sizeof(*stp));
		stp->num = i;
		err = pthread_create(tid+i-100,NULL,myfunc,stp);
		if(err)
		{
			fprintf(stderr,"pthread_create:%s\n",strerror(err));
			exit(1);
		}
	}
	for(i = 0;i<100;i++)
	{
		pthread_join(tid[i],&ptr);
		free(ptr);
	}
	return 0;
}
void *myfunc(void *arg)
{
	int i = ((struct mynum *)arg)->num;
	int j=0,mark=1;
	for(j = 2;j < (i>>2);j++)
	{
		if((i%j) == 0)
		{
			mark = 0;
			break;
		}
	}
	if(mark == 1)
	{
		printf("primer:%d\n",i);
	}
	pthread_exit(arg);
}




















