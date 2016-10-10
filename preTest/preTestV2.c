//2nd pretest
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>

#define number_o_threads 4
typedef struct thread{

        char character_name[30];
	char symbol;
        int  thread_num;
	int  position_xy[2];
	int  condition;
        pthread_t thread_id;

}thread_data;

struct mutex_shared{

        int BOARD[5][5];
        int FINISH;
	int WINNER;
	int FLAG[2];
	int CONDITION;
	char CHARACTER_WITH_CARROT[30];

} SHARED_DATA;

pthread_mutex_t object_mutex;

void magic(thread_data *objects);
void printGrid();
void init_data(thread_data *objects);
void place(thread_data *objects, int number);
int  getRandom(int rangeLow, int rangeHigh);

void magic(thread_data *objects){

	pthread_mutex_lock(&object_mutex);

		//handles Shared_DATA inside lock
		if(SHARED_DATA.CONDITION == objects->condition){

			SHARED_DATA.CONDITION = objects->thread_num;
			SHARED_DATA.BOARD[objects->position_xy[1]][objects->position_xy[0]] = '-';
			place(objects, objects->thread_num);
			SHARED_DATA.BOARD[objects->position_xy[1]][objects->position_xy[0]] = objects->symbol;
			if(objects->position_xy[1] == SHARED_DATA.FLAG[1] && objects->position_xy[0] == SHARED_DATA.FLAG[0]){

				strcpy(SHARED_DATA.CHARACTER_WITH_CARROT, objects->character_name);
				SHARED_DATA.WINNER = 1;
			}


			printf("%s moved to x= %d y= %d", objects->character_name, objects->position_xy[0], objects->position_xy[1]);

		}

	pthread_mutex_unlock(&object_mutex);
}

void *API(void *thread){

        thread_data *objects = (thread_data *)thread;

        // do things here
	while(SHARED_DATA.WINNER != 1){

		magic(objects);
		sleep(2);

		//for(int i=0; i<4; i++){

                	//srandom((unsigned int) time.tv_usec);
                	//place(objects, objects[i].thread_num);
                	//printf("name: %s, symbol: %c, thread_num: %d\n", objects[i].character_name, objects[i].symbol, objects[i].thread_num);
                	//printf("position 0x = %d position 1y = %d\n", objects[i].position_xy[0], objects[i].position_xy[1]);
                	//printf("-----------------------------------------------\n");
        	//}
		printGrid();

	}

	printf("%s wins", SHARED_DATA.CHARACTER_WITH_CARROT);

        pthread_exit(NULL);

}

void printGrid(){

	for(int i=0; i<5; i++){

		for(int j=0; j<5; j++){

			printf("%c", SHARED_DATA.BOARD[i][j]);
		}
		printf("\n");
	}
	//printf("here");

	//return 0;

}

int getRandom(int rangeLow, int rangeHigh)
{
        double myRand = rand()/(1.0 + RAND_MAX);
        int range = rangeHigh - rangeLow + 1;
        int myRand_scaled = (myRand * range) + rangeLow;
        return myRand_scaled;
}

void place(thread_data *objects, int number){

	int rand1 = getRandom(0,4);
	int rand2 = getRandom(0,4);

	while(1){
		for(int i=0; i<4; i++){

			if(number != i){
				if(rand1 != objects[i].position_xy[0] || rand2 != objects[i].position_xy[1]){

					objects[number].position_xy[0] = rand1;
					objects[number].position_xy[1] = rand2;
					return;
				}
			}
		}
		rand1 = getRandom(0,4);
		rand2 = getRandom(0,4);
	}
}

void init_data(thread_data *objects){

        //where we handle all info before I spawn threads

        for(int i=0; i<5; i++){

		for(int j=0; j<5; j++){

			SHARED_DATA.BOARD[i][j] = '-';
		}
	}

	printGrid();

	SHARED_DATA.CONDITION = 3;
	SHARED_DATA.FLAG[0] = getRandom(0,4);
	SHARED_DATA.FLAG[1] = getRandom(0,4);

	//printf("hello");
	objects[0].symbol     = 'B';
	objects[0].thread_num = 0;
	objects[0].condition   = 3;
	strcpy(objects[0].character_name, "Bunny");

	objects[1].symbol     = 'D';
	objects[1].thread_num = 1;
	objects[1].condition  = 0;
	strcpy(objects[1].character_name, "Taz D");

	objects[2].symbol     = 'T';
	objects[2].thread_num = 2;
	objects[2].condition  = 1;
	strcpy(objects[2].character_name, "Tweety");

	objects[3].symbol     = 'M';
	objects[3].thread_num = 3;
	objects[3].condition  = 2;
	strcpy(objects[3].character_name, "Marvin");

	for(int i=0; i<4; i++){

		//srandom((unsigned int) time.tv_usec);
		place(objects, objects[i].thread_num);
		printf("name: %s, symbol: %c, thread_num: %d\n", objects[i].character_name, objects[i].symbol, objects[i].thread_num);
		printf("position 0x = %d position 1y = %d\n", objects[i].position_xy[0], objects[i].position_xy[1]);
		printf("-----------------------------------------------\n");
	}

	for(int i=0; i<4; i++){

		//1 for y 0 for x
		SHARED_DATA.BOARD[objects[i].position_xy[1]][objects[i].position_xy[0]] = objects[i].symbol;

	}

	SHARED_DATA.BOARD[SHARED_DATA.FLAG[1]][SHARED_DATA.FLAG[0]]= 'c';

	printGrid();
	//gettimeofday(&time, NULL);
	//do random things
	//SHARED_DATA.BOARD[][] = 'T()';

}


int main(int argc, char *argv[]){

	struct timeval time;
	thread_data thread[number_o_threads];

	gettimeofday(&time, NULL);
	srandom((unsigned int) time.tv_usec);

        init_data(thread);

        pthread_mutex_init(&object_mutex, NULL);

	for(int i=0; i<number_o_threads; i++){

                thread[i].thread_num = i;
                pthread_create(&(thread[i].thread_id), NULL, API,(void *)(&thread[i]));
        }

	for(int i=0; i<number_o_threads; i++){
		pthread_join(thread[i].thread_id, NULL);
	}
	//pthread_mutex_destroy(&object_mutex);
	return 0;
}

