#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define number_of_toons 3

typedef struct thread{
	pthread_t thread_id;
	int distance, freeze, thread_num, condition;
	char character[30];
} thread_data;

pthread_mutex_t toons_mutex;

int COUNT_GLOBAL, CONDITION_VAR;

void init_data(thread_data *toons);
int  freeze_em(int rangeLow, int rangeHigh);
void race(thread_data *toons);

void init_data(thread_data *toons){

	COUNT_GLOBAL  = 0;

	//debug
	printf("suh \n");
	toons[0].distance = 0;
	toons[0].freeze   = 0;
	strcpy(toons[0].character, "tweety");

	toons[1].distance = 0;
	toons[1].freeze   = 0;
	strcpy(toons[1].character, "muttley");

	toons[2].distance = 0;
	toons[2].freeze   = 0;
	strcpy(toons[2].character, "marvin");
}

int freeze_em(int rangeLow, int rangeHigh){

	double myRand = rand()/(1.0 + RAND_MAX);
	int range = rangeHigh - rangeLow + 1;
	int myRand_scaled = (myRand * range) + rangeLow;
	return myRand_scaled;
}

void race(thread_data *toons){

	pthread_mutex_lock(&toons_mutex);

		struct timeval time;
        	gettimeofday(&time,NULL);
        	srandom((unsigned int) time.tv_usec);

		if(CONDITION_VAR == toons->thread_num){

			//debug
			//printf("its odd and doing things\n");
			toons->freeze = freeze_em(0,1);
			if(toons->freeze != 1){

				toons->distance ++;
			}

			printf("character = %s distance = %d\n", toons->character, toons->distance);
		}
		COUNT_GLOBAL ++;
	pthread_mutex_unlock(&toons_mutex);
}

void *API(void *thread){

	thread_data *toons = (thread_data*)thread;

	while(COUNT_GLOBAL<10){
		//debug
		//printf("init to win it\n");
		race(toons);
		sleep(2);
		printf("done\n");
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[]){

	thread_data thread[number_of_toons];

	init_data(thread);

	CONDITION_VAR = 0;

	for(int i=0; i<number_of_toons; i++){

		printf("character = %s distance = %d\n", thread[i].character, thread[i].distance);
	}

	pthread_mutex_init(&toons_mutex, NULL);

	for(int i=0; i<number_of_toons; i++){

		thread[i].thread_num = i;
		pthread_create(&(thread[i].thread_id), NULL, API, (void *)(&thread[i]));
	}

	for(int i=0; i<number_of_toons; i++){

		pthread_join(thread[i].thread_id, NULL);
	}


	printf("here?");
	pthread_mutex_destroy(&toons_mutex);

	return 0;
}
