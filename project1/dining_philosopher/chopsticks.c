#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include "philosopher.h"
pthread_mutex_t mutex[5];
/*
 * Performs necessary initialization of mutexes.
 */
void chopsticks_init(){
	int i;
	for (i = 0; i < 5; i++){
		assert(!pthread_mutex_init(&mutex[i],NULL));
    }
}

/*
 * Cleans up mutex resources.
 */
void chopsticks_destroy(){
	int i;
	for (i = 0; i < 5; i++){
		assert(!pthread_mutex_destroy(&(mutex[i])));
	}
}

/*
 * Uses pickup_left_chopstick and pickup_right_chopstick
 * to pick up the chopsticks
 */   
void pickup_chopsticks(int phil_id){
	while(1){
            	pthread_mutex_lock(&mutex[phil_id]);
		if (!pthread_mutex_trylock(&mutex[(phil_id+1)%5])){
			pickup_left_chopstick(phil_id);
			pickup_right_chopstick(phil_id);
			break;			
		}
		else{
			pthread_mutex_unlock(&mutex[phil_id]);			
		}
	}
}

/*
 * Uses pickup_left_chopstick and pickup_right_chopstick
 * to pick up the chopsticks
 */   
void putdown_chopsticks(int phil_id){
	putdown_right_chopstick(phil_id); //putdown right chopstick
	pthread_mutex_unlock(&mutex[(phil_id+1)%5]); //unlock the right lock
	putdown_left_chopstick(phil_id); //putdown left chopstick
	pthread_mutex_unlock(&mutex[phil_id]); //unlock the left lock
}
