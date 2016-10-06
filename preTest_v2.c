#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define number_o_threads 3
typedef struct thread{

	char character_name[30];
	int  thread_num;
	int  position, frozen,condition;
	pthread_t thread_id;

}thread_data;

struct mutex_shared{

	int BOARD[2][9];
	int FINISH;
	int WINNER;
	int LATEST_CONDITION;
} SHARED_DATA;

pthread_mutex_t object_mutex;

void magic(thread_data *objects);
void init_data(thread_data *objects);

void magic(thread_data *objects){

	pthread_mutex_lock(&object_mutex);

		//handle SHARED_DATA inside lock
		

	pthread_mutex_unlock(&object_mutex);


}

void *API(void *thread){

	thread_data *objects = (thread_data *)thread;

	// do things here
	while(SHARED_DATA.WINNER != 1){

		magic(objects);
		sleep(2);

	}

	pthread_exit(NULL);

}

void init_data(thread_data *objects){

	//where we handle all info before I spawn threads

	for(int i=0; i<2; i++){

		for(int j=0; j<9; j++){
			SHARED_DATA.BOARD[i][j] = '-';
		}
	}

	SHARED_DATA[0][]

	SHARED_DATA.FINISH = 0;
	SHARED_DATA.WINNER = 0;
	SHARED_DATA.LATEST_CONDITION = 2;

	objects[0].position  = 0;
	objects[0].frozen    = 0;
	objects[0].condition = 2;
	strcpy(objects[0].character_name, "Tweety");

	objects[1].position  = 0;
	objects[1].frozen    = 0;
	objects[1].condition = 0;
	strcpy(objects[1].character_name, "Muttley");

	objects[2].position  = 0;
	objects[2].frozen    = 0;
	objects[2].condition = 1;
	strcpy(objects[2].character_name, "Marvin");


}

int main(int argc, char *argv[]){


	thread_data thread[number_o_threads];

	init_data(thread);

	pthread_mutex_init(&object_mutex, NULL);

	for(int i=0; i<number_o_threads; i++){

		thread[i].thread_num = i;
		pthread_create(&(thread[i].thread_id), NULL, API,(void *)(&thread[i]));
	}

	for(int i=0; i<number_o_threads; i++){

                pthread_join(thread[i].thread_id, NULL);
        }

        pthread_mutex_destroy(&object_mutex);
        return 0;
}
