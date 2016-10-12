// first preTEST
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>

#define number_o_threads 3   // actuall threads you want run
#define number_o_objects 3   // thread struct objects to be made
#define BoardX           10  // how many units in the x direction the graph is
#define BoardY           2   // same as above but y

// what you pass to thread
typedef struct thread{

        char character_name[30];
	char symbol;
        int  thread_num;
	int  condition;
	int  frozen;
	int  position;
        pthread_t thread_id;

}thread_data;

// global scope
struct mutex_shared{

        int  BOARD[BoardY][BoardX];
	int  WINNER;
	int  CONDITION;

} SHARED_DATA;

pthread_mutex_t object_mutex;

void magic(thread_data *objects);
void printGrid();
void init_data(thread_data *objects);
void place(thread_data *objects, int number);
void move_object(thread_data *objects);
int  getRandom(int rangeLow, int rangeHigh, struct timeval time);

//keep
void move_object(thread_data *objects){

	struct timeval time;

        pthread_mutex_lock(&object_mutex);

	if(SHARED_DATA.CONDITION == objects->condition && SHARED_DATA.WINNER != 1){

		SHARED_DATA.CONDITION = objects->thread_num;

		if(objects->frozen == 0 && objects->thread_num != 2){

			SHARED_DATA.BOARD[objects->thread_num][objects->position] = '-';

			printf("%s moved one space\n",objects->character_name);
			objects->position++;

			SHARED_DATA.BOARD[objects->thread_num][objects->position] = objects->symbol;

		}else if(objects->thread_num == 2){


			if(objects[0].frozen == 1){
				objects[0].frozen = 0; 
			}else{
				objects[0].frozen = getRandom(0,1,time);
			}

			if(objects[1].frozen == 1){
				objects[1].frozen = 0;
			}else{
				objects[1].frozen = getRandom(0,1,time);
			}

		}else{

			printf("%s is frozen\n", objects->character_name);
		}

		if(objects->position >= 9){
			SHARED_DATA.WINNER = 1;
			printf("%s wins !", objects->character_name);
		}
	}

	printf("shared %d, objects %d\n",SHARED_DATA.CONDITION, objects->condition);

	printGrid();
        pthread_mutex_unlock(&object_mutex);
}



//keep
void *API(void *thread){

	static int count = 0;
        thread_data *objects = (thread_data *)thread;

        // do things here
	while(SHARED_DATA.WINNER != 1){

		move_object(objects);
		sleep(2);
	}

        pthread_exit(NULL);

}

//keep
void printGrid(){

	for(int i=0; i<BoardY; i++){

		for(int j=0; j<BoardX; j++){

			printf("%c", SHARED_DATA.BOARD[i][j]);
		}
		printf("\n");
	}
}

// keep
int getRandom(int rangeLow, int rangeHigh, struct timeval time){

	gettimeofday(&time, NULL);
        srandom((unsigned int) time.tv_usec);

        double myRand = rand()/(1.0 + RAND_MAX);
        int range = rangeHigh - rangeLow + 1;
        int myRand_scaled = (myRand * range) + rangeLow;
        return myRand_scaled;
}

//keep
void init_data(thread_data *objects){

	struct timeval time;

        //where we handle all info before I spawn threads
        for(int i=0; i<BoardY; i++){

		for(int j=0; j<BoardX; j++){

			SHARED_DATA.BOARD[i][j] = '-';
		}
	}
	// double check the grid
	printGrid();

	SHARED_DATA.CONDITION = 2;

	//define all your objects
	objects[0].symbol      = 'T';
	objects[0].thread_num  =  0;
	objects[0].condition   =  2;
	objects[0].frozen      =  0;
	objects[0].position    =  0;
	strcpy(objects[0].character_name, "Tweety");

	objects[1].symbol      = 'M';
	objects[1].thread_num  =  1;
	objects[1].condition   =  0;
	objects[1].frozen      =  0;
	objects[1].position    =  0;
	strcpy(objects[1].character_name, "Muttley");

	objects[2].symbol      = 'A';
	objects[2].thread_num  =  2;
	objects[2].condition   =  1;
	objects[2].frozen      =  0;
	objects[2].position    =  0;
	strcpy(objects[2].character_name, "Marvin");


	for(int i=0; i<number_o_objects; i++){

		printf("name: %s, symbol: %c, thread_num: %d\n", objects[i].character_name, objects[i].symbol, objects[i].thread_num);
		printf("-----------------------------------------------\n");
	}

	SHARED_DATA.BOARD[0][0] = objects[0].symbol;
	SHARED_DATA.BOARD[1][0] = objects[1].symbol;
	printGrid();

}


int main(int argc, char *argv[]){

	thread_data thread[number_o_objects];
        init_data(thread);
        pthread_mutex_init(&object_mutex, NULL);


	//comment out to check to see if init_data works
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

