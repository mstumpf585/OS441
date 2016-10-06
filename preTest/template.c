#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define number_o_threads 3
typedef struct thread{

        char character_name[30];
        int thread_num;
        int position, frozen,condition;
        pthread_t thread_id;

}thread_data;

struct mutex_shared{

        int BOARD[9][9];
        int FINISH;
	int WINNER;

} SHARED_DATA;

pthread_mutex_t object_mutex;

void magic(thread_data *objects){

	pthread_mutex_lock(&object_mutex);

		//handles Shared_DATA inside lock

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

