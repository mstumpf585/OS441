/*
 * gold_bomb.c
 *
 *  Created on: Sep 1, 2016
 *      Author: michael
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

//-----------------------------------------------------------------
int  GLOBAL_COUNT;
int  gold1_xy[2];
int  gold2_xy[2];
bool gold1_found;
bool gold2_found;
char grid[4][4];

pthread_mutex_t robot_mutex;

//------------------------------------------------------------------
typedef struct thread{

	int  robot_xy[2];
} thread_object;

//------------------------------------------------------------------
int getRandom(int rangeLow, int rangeHigh)
{
	double myRand = rand()/(1.0 + RAND_MAX);
	int range = rangeHigh - rangeLow + 1;
	int myRand_scaled = (myRand * range) + rangeLow;
	return myRand_scaled;
}

void print_grid();
void print_grid(){

	for(int i=0; i<4; i++){

		for(int j=0; j<4; j++){

			printf(" | ");
			printf("%c", grid[i][j]);
		}
		printf(" | \n");
	}

}

void randomBomb(thread_object *objects);
void randomBomb(thread_object *objects)
{
	int random [2];
	for(int i =0; i<2;i++)
	{
		random[i] = getRandom(0,3);
	}
	grid[random[0]][random[1]] = 'b';
	objects->robot_xy[0]=random[0];
	objects->robot_xy[1]=random[1];
}

void randomGold();
void randomGold()
{
	int random [2];
	bool conflicts = true;

	for(int i = 0; i < 2; i++)
	{
		while(conflicts == true)
		{
			for(int i =0; i<2;i++)
			{
				random[i] = getRandom(0,3);
			}
			if(grid[random[0]][random[1]] != 'b' && grid[random[0]][random[1]] != 'g')
			{
				conflicts = false;
			}
		}
		conflicts = true;
		grid[random[0]][random[1]] = 'g';
		if( i == 0)
		{
			gold1_xy[0]=random[0];
			gold1_xy[1]=random[1];
		}
		if( i == 1)
		{
			gold2_xy[0]=random[0];
			gold2_xy[1]=random[1];
		}
	}
}

void randomRobot(thread_object *objects);
void randomRobot(thread_object *objects)
{
	int random [2];
	bool conflicts = true;

	while(conflicts == true)
	{
		for(int i =0; i<2;i++)
		{
			random[i] = getRandom(0,3);
		}
		if(grid[random[0]][random[1]] != 'b' && grid[random[0]][random[1]] != 'g')
		{
			conflicts = false;
		}
	}
	grid[random[0]][random[1]] = 'r';
	objects->robot_xy[0]=random[0];
	objects->robot_xy[1]=random[1];

}


void is_gold(thread_object *object);
void is_gold(thread_object *object)
{
		if((gold1_xy[0] == object->robot_xy[0] && gold1_xy[1] == object->robot_xy[1])&& gold1_found == 0)
		{
			printf("gold found at %d,%d \n",object->robot_xy[0],object->robot_xy[1]);
			gold1_found = 1;
		}
		if((gold2_xy[0] == object->robot_xy[0] && gold2_xy[1] == object->robot_xy[1])&& gold2_found == 0)
		{
			printf("gold found at %d,%d \n",object->robot_xy[0],object->robot_xy[1]);
			gold2_found = 1;
		}
}

bool is_still_gold();
bool is_still_gold()
{
	if(gold1_found == 0 || gold2_found == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void move_robot(thread_object *objects);
void move_robot(thread_object *objects){

	//todo move robot around switch statements
	// use 0-7 random numbers so we know where to move robot
	// 765
	// 4R3
	// 210

	// generate random num move to corresponding spot relative to R 
	// check to see if spot is valid else loop back
	// implementing now 4:14 pm 9/6
	int xcord = 0;
	int ycord = 0;

	int random_number = 0;
	while(1){


		//scanf("%d", &random_number);
                random_number = getRandom(0,7);
                xcord = objects->robot_xy[1];
                ycord = objects->robot_xy[0];

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
                                break;
                }

                if((xcord >= 0 && xcord <= 3) && (ycord >= 0 && ycord <= 3)){
                        if(grid[ycord][xcord] != 'b'){

                                grid[objects->robot_xy[0]][objects->robot_xy[1]] = '-';
                                grid[ycord][xcord] = 'R';
                                objects->robot_xy[1] = xcord;
                                objects->robot_xy[0] = ycord;
                                break;

                        }else{
                                xcord = objects->robot_xy[1];
                                ycord = objects->robot_xy[0];
                        }
                }else{

                        xcord = objects->robot_xy[1];
                        ycord = objects->robot_xy[0];
                }
        }

        printf("xcord = %d and ycord = %d \n", xcord, ycord);
        print_grid();
}


void make_workspace(thread_object *objects);
void make_workspace(thread_object *objects){

	for(int i=0; i<4; i++){

		for(int j=0; j<4; j++){

			grid[i][j] = '-';
		}
	}

	randomBomb(objects[0]);
	randomGold();
	randomRobot(objects[1]);
	print_grid();
}

//void API(void *thread){


//}

//function: main
int main(int argc, char* argv[])
{

	thread_object thread[2];
	struct timeval time;
	gettimeofday(&time, NULL);

	srandom((unsigned int) time.tv_usec);

	printf("here we go \n");

	gold1_found = false;
	gold2_found = false;

	make_workspace(thread);

	pthread_mutex_init(&robot_mutex, NULL);
	printf("All gold found, terminating \n");
	//free(object);
}
