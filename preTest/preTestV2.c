//2nd pretest
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <unistd.h>

#define number_o_threads 4  // actuall threads you want run
#define number_o_objects 7  // thread struct objects to be made
#define BoardX           5  // how many units in the x direction the graph is
#define BoardY           5  // same as above but y

int count = 0;
// what you pass to thread
typedef struct thread{

        char character_name[30];
	char symbol;
        int  thread_num;
	int  position_xy[2];
	int  condition;
        pthread_t thread_id;

}thread_data;

// global scope
struct mutex_shared{

        int  BOARD[BoardY][BoardX];
	int  WINNER;
	char FLAG[2];
	int  CONDITION;
	int  CARROT1[2];
	int  CARROT2[2];
	int  MOUNTAIN[2];
	int  WHO_DEAD[4];

} SHARED_DATA;

int mountain_count = 0;

pthread_mutex_t object_mutex;

void magic(thread_data *objects);
void printGrid();
void init_data(thread_data *objects);
void place(thread_data *objects, int number);
void move_object(thread_data *objects);
void kill_toon(thread_data *objects, int ycord, int xcord);
void clear(thread_data *objects, int ycord, int xcord);
void move_mountain();
int  getRandom(int rangeLow, int rangeHigh, struct timeval time);

//don't keep
void move_mountain(){

	struct timeval time;

	int xcord;
	int ycord;
	int stop = 0;

	SHARED_DATA.BOARD[SHARED_DATA.MOUNTAIN[0]][SHARED_DATA.MOUNTAIN[1]] = '-';

	while(stop != 1){

		xcord = getRandom(0,5,time);
		ycord = getRandom(0,5,time);

		if(SHARED_DATA.BOARD[ycord][xcord] == '-'){

			stop = 1;
			SHARED_DATA.BOARD[ycord][xcord] = 'F';
			SHARED_DATA.MOUNTAIN[0] = ycord;
			SHARED_DATA.MOUNTAIN[1] = xcord;
		}
	}

	//debug
	printf("mountain at x=%d, y=%d\n", xcord, ycord);
}

//dont need to keep just to help with kill toons for midterm 2
void kill_toon(thread_data *objects, int ycord, int xcord){

	int dead_object = 0;

	char dead_character[30];

	switch(SHARED_DATA.BOARD[ycord][xcord]){

		case 'B':
			dead_object = 0;
			strcpy(dead_character,"Bunny");
			break;

		case 'D':
			dead_object = 1;
			strcpy(dead_character,"Taz");
			break;

		case 'T':
			dead_object = 2;
			strcpy(dead_character,"Tweety");
			break;
	}
	SHARED_DATA.WHO_DEAD[dead_object] = 0;

	if(SHARED_DATA.BOARD[ycord][xcord] == SHARED_DATA.FLAG[0] || SHARED_DATA.BOARD[ycord][xcord] == SHARED_DATA.FLAG[1]){

		if(SHARED_DATA.FLAG[0] == 'M'){

			SHARED_DATA.BOARD[ycord][xcord] = 'C';
			SHARED_DATA.FLAG[1] = 'Z';

		}else if(SHARED_DATA.FLAG[1] == 'M'){

			SHARED_DATA.BOARD[ycord][xcord] = 'C';
			SHARED_DATA.FLAG[0] = 'Z';

		}else if(SHARED_DATA.BOARD[ycord][xcord] == SHARED_DATA.FLAG[0]){

			printf("in\n");
			clear(objects, ycord, xcord);
			SHARED_DATA.FLAG[0] = 'M';

		}else if(SHARED_DATA.BOARD[ycord][xcord] == SHARED_DATA.FLAG[1]){

			printf("in\n");
			clear(objects,ycord,xcord);
			SHARED_DATA.FLAG[1] = 'M';
		}
	}else{
		clear(objects,ycord,xcord);
	}
	printf("%s is dead\n",dead_character);


}

// don't keep
void clear(thread_data *objects, int ycord, int xcord ){

	SHARED_DATA.BOARD[objects->position_xy[0]][objects->position_xy[1]] = '-';
        objects->position_xy[0] = ycord;
        objects->position_xy[1] = xcord;
        SHARED_DATA.BOARD[ycord][xcord] = objects->symbol;
}

//keep
void move_object(thread_data *objects){

	pthread_mutex_lock(&object_mutex);

	if(SHARED_DATA.CONDITION == objects->condition){

		SHARED_DATA.CONDITION = objects->thread_num;

		struct timeval time;

        	int xcord = 0;
        	int ycord = 0;
        	int random_number = 0;
		int print = 1;
		int count = 0;
		int stop  = 0;

        	while(stop != 1){

                	random_number = getRandom(0,7,time);
                	xcord = objects->position_xy[1];
                	ycord = objects->position_xy[0];

                	switch(random_number){

                        	case 7:
                                	// up one left one
                                	xcord = xcord -  1;
                                	ycord = ycord -  1;
                                	break;

                        	case 6:
                                	// up one
                                	ycord -= 1;
                                	break;

                        	case 5:
                                	//up one right one
                                	xcord += 1;
                                	ycord -= 1;
                                	break;

                        	case 4:
				 	// left one
                                	xcord -= 1;
                                	break;

                        	case 3:
                                	// right one
                                	xcord += 1;
                                	break;

                        	case 2:
                                	//down left
                                	xcord -= 1;
                                	ycord += 1;
                                	break;

                        	case 1:
                                	// down
                                	ycord += 1;
                                	break;

                        	case 0:
                                	// down right
                                	xcord += 1;
                                	ycord += 1;
			}

                	if((xcord >= 0 && xcord < BoardX) && (ycord >= 0 && ycord < BoardY)){



				if(SHARED_DATA.BOARD[ycord][xcord] =='-' && objects->symbol != 'M' && SHARED_DATA.WHO_DEAD[objects->thread_num] == 1){

					clear(objects, ycord, xcord);
					stop = 1;

				}else if(SHARED_DATA.BOARD[ycord][xcord] == 'C' && SHARED_DATA.WHO_DEAD[objects->thread_num] == 1 
					&& (SHARED_DATA.FLAG[0] != objects->symbol && SHARED_DATA.FLAG[1] != objects->symbol)){

					clear(objects, ycord, xcord);
					if(SHARED_DATA.CARROT1[0] == ycord && SHARED_DATA.CARROT1[1] == xcord){

						SHARED_DATA.FLAG[0] = objects->symbol;
					}else{

						SHARED_DATA.FLAG[1] = objects->symbol;
					}

					printf("%s , thread num = %d has the flag\n", objects->character_name, objects->thread_num);
					stop = 1;

				}else if((SHARED_DATA.BOARD[ycord][xcord] == 'F') && (objects->symbol == SHARED_DATA.FLAG[0] || objects->symbol == SHARED_DATA.FLAG[1])){

					clear(objects, ycord, xcord);
					printf("%s just won\n", objects->character_name);
					SHARED_DATA.WINNER = 1;
					stop = 1;

				}else if((SHARED_DATA.BOARD[ycord][xcord] != 'F' && SHARED_DATA.BOARD[ycord][xcord] != 'C') && objects->symbol == 'M' ){

					if(SHARED_DATA.BOARD[ycord][xcord] != '-'){

						printf("%c is the symbol before death\n", SHARED_DATA.BOARD[ycord][xcord]);
						kill_toon(objects, ycord, xcord);
					}else{

						clear(objects, ycord, xcord);
					}

					mountain_count++;
					if(mountain_count == 3){

						printf("moving mountain\n");
						move_mountain(ycord,xcord);
						mountain_count = 0;
					}
					stop = 1;

				}else if(SHARED_DATA.WHO_DEAD[objects->thread_num]==0){

					printf("Skipping %s\n", objects->character_name);
					print = 0;
					stop = 1;
				}else{

					print = 0;
					printf("no condition\n");
					ycord = objects->position_xy[0];
					xcord = objects->position_xy[1];
					count++;
					if(count > 10){

						stop = 1;

						printf("dump \n symbol %c, name %s, number %d\n", objects->symbol, objects->character_name, objects->thread_num);
						printf("condition %d, position xy %d %d\n", objects->condition, objects->position_xy[1],objects->position_xy[0]);
						printf("--------------------------------------------------------------------------------------------\n");
						printf("shared \n");
						printf("flag[0] %c, flag[1] %c, conditoin %d\n",SHARED_DATA.FLAG[0], SHARED_DATA.FLAG[1], SHARED_DATA.CONDITION);
						printf("who dead 1%d 2%d 3%d 4%d", SHARED_DATA.WHO_DEAD[0], SHARED_DATA.WHO_DEAD[1], SHARED_DATA.WHO_DEAD[2], SHARED_DATA.WHO_DEAD[3]);
					}
				}
       	 		}
		}

		if(print == 1){
			printGrid();
			printf("%s moved to x= %d, y= %d\n",objects->character_name, xcord, ycord);
			printf("--------------------------\n");
		}

	}
	pthread_mutex_unlock(&object_mutex);
}



//keep
void *API(void *thread){

	static int count = 0;
        thread_data *objects = (thread_data *)thread;

        // do things here
	while(SHARED_DATA.WINNER != 1){

		//printf("here\n");
		move_object(objects);
		sleep(2);
	}

        pthread_exit(NULL);

}

//keep ONLY USE AT START!!!!!!!!
void place(thread_data *objects, int number){

	// 1 for x 0 for y
	struct timeval time;
	int randx = getRandom(0,BoardX-1,time);
	int randy = getRandom(0,BoardY-1,time);
	int match = 0;

	while(1){
		for(int i=0; i<number_o_objects; i++){

			// debug: printf("number = %d, i= %d \n", number, i);
			if(number != i){
				if(randy == objects[i].position_xy[0] && randx == objects[i].position_xy[1]){

					match = 1;
				}
			}
		}

		if(match == 1){
			randx = getRandom(0,BoardX-1,time);
			randy = getRandom(0,BoardY-1,time);

			match = 0;
		}else{

			objects[number].position_xy[0] = randy;
			objects[number].position_xy[1] = randx;

			return;
		}
	}
}

//keep
void printGrid(){

	for(int i=0; i<BoardY; i++){

		for(int j=0; j<BoardX; j++){

			if(SHARED_DATA.FLAG[0] == SHARED_DATA.BOARD[i][j] || SHARED_DATA.FLAG[1] == SHARED_DATA.BOARD[i][j]){
				printf("c%c|", SHARED_DATA.BOARD[i][j]);
			}else{
				printf(" %c|", SHARED_DATA.BOARD[i][j]);
			}
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

	SHARED_DATA.CONDITION = 3;
	SHARED_DATA.FLAG[0] = 'z';
	SHARED_DATA.FLAG[1] = 'z';

	//define all your objects
	objects[0].symbol      = 'B';
	objects[0].thread_num  = 0;
	objects[0].condition   = 3;
	strcpy(objects[0].character_name, "Bunny");

	objects[1].symbol      = 'D';
	objects[1].thread_num  = 1;
	objects[1].condition   = 0;
	strcpy(objects[1].character_name, "Taz D");

	objects[2].symbol     = 'T';
	objects[2].thread_num = 2;
	objects[2].condition  = 1;
	strcpy(objects[2].character_name, "Tweety");

	objects[3].symbol     = 'M';
	objects[3].thread_num = 3;
	objects[3].condition  = 2;
	strcpy(objects[3].character_name, "Marvin");

	objects[4].symbol     = 'F';
	objects[4].thread_num = 4;
	objects[4].condition  = 9999;
	strcpy(objects[4].character_name, "Mountain");

	objects[5].symbol     = 'C';
	objects[5].thread_num = 5;
	objects[5].condition  = 9999;
	strcpy(objects[5].character_name, "Carrot");

	objects[6].symbol     = 'C';
	objects[6].thread_num = 6;
	objects[6].condition  = 9999;
	strcpy(objects[6].character_name, "Carrot");

	for(int i=0; i<number_o_objects; i++){

		place(objects, objects[i].thread_num);
		printf("name: %s, symbol: %c, thread_num: %d\n", objects[i].character_name, objects[i].symbol, objects[i].thread_num);
		printf("position 1=x = %d position 0=y = %d\n", objects[i].position_xy[1], objects[i].position_xy[0]);
		printf("-----------------------------------------------\n");
	}

	// put all object symbols on board
	for(int i=0; i<number_o_objects; i++){

		//0 for y 1 for x
		SHARED_DATA.BOARD[objects[i].position_xy[0]][objects[i].position_xy[1]] = objects[i].symbol;

	}


	//did not think ahead so its dumb ...
	SHARED_DATA.WHO_DEAD[0] = 1;
	SHARED_DATA.WHO_DEAD[1] = 1;
	SHARED_DATA.WHO_DEAD[2] = 1;
	SHARED_DATA.WHO_DEAD[3] = 1;

	SHARED_DATA.CARROT1[0] = objects[5].position_xy[0];
	SHARED_DATA.CARROT1[1] = objects[5].position_xy[1];

	SHARED_DATA.CARROT2[0] = objects[6].position_xy[0];
	SHARED_DATA.CARROT2[1] = objects[6].position_xy[1];

	SHARED_DATA.MOUNTAIN[0] = objects[4].position_xy[0];
	SHARED_DATA.MOUNTAIN[1] = objects[4].position_xy[1];
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

