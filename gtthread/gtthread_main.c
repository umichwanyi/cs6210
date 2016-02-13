#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

/* Tests creation.
   Should print "Hello World!" */

void *thr1(void *in) {
  	printf("Hello World!\n");
	long i = 0;
	int j = 0;
	while(j != 100){
		i = 0;
		while(i < 1000000){
			i++;
		}
		printf ("%d, j=%d\n",*((int*)in), j);
		fflush(stdout);
		j++;
		//gtthread_yield();
			
	}
	printf("%d finish\n",*((int*)in));
  	
}

int main() {
	printf("gtthread_init\n");
	fflush(stdout);
  	gtthread_t t1,t2,t3;
	fflush(stdout);
  	gtthread_init(1);
	int a = 1;
	int b = 2;
	int c = 3;
  	gtthread_create( &t1, thr1, &a);
	gtthread_create( &t2, thr1, &b);
	gtthread_create( &t3, thr1, &c);
	printf("create finish\n");
	//fflush(stdout);
	int j = 0;
	long i;
	while(j != 50){
		i = 0;
		while(i<100000){
			i++;
			//printf("***\n");
		}
		printf ("main\n");
		fflush(stdout);
		//printf("self id = %d\n",gtthread_self().id);
		j++;
		//gtthread_yield();	
		
	}
	printf("main finish\n");
	gtthread_exit(0);
  //gtthread_yield();

  //return EXIT_SUCCESS;
}
