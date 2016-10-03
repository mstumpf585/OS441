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

struct workspace{
	 char grid[4][4];
};

struct objects{

	int  gold1_xy[2];
	bool gold1_found;
	int  gold2_xy[2];
	bool gold2_found;
};

typedef struct thread{

	pthread_t 	  thread_id;
	int               thread_num;
	int               cord_xy[2];
	struct objects   *the_objects;
	struct workspace *the_grid;
} thread_data;

pthread_mutex_t thread_mutex;



int getRandom(int rangeLow, int rangeHigh)
{
	double myRand = rand()/(1.0 + RAND_MAX);
	int range = rangeHigh - rangeLow + 1;
	int myRand_scaled = (myRand * range) + rangeLow;
	return myRand_scaled;
}

void print_grid(struct workspace *workspace_data);
void print_grid(struct workspace *workspace_data){

	for(int i=0; i<4; i++){

		for(int j=0; j<4; j++){

			printf(" | ");
			printf("%c", workspace_data->grid[i][j]);
		}
		printf(" | \n");
	}

}

void randomBomb(thread_data *thread, struct workspace *workspace_data);
void randomBomb(thread_data *thread, struct workspace *workspace_data)
{

	int random [2];
	for(int i =0; i<2;i++)
	{
		random[i] = getRandom(0,3);
	}

	workspace_data->grid[random[0]][random[1]] = 'b';

	// zero for bomb
	thread[0].cord_xy[0]=random[0];
	thread[0].cord_xy[1]=random[1];
}

void randomGold(struct workspace *workspace_data, struct objects *objects);
void randomGold(struct workspace *workspace_data, struct objects *objects)
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
			if(workspace_data->grid[random[0]][random[1]] != 'b' && workspace_data->grid[random[0]][random[1]] != 'g')
			{
				conflicts = false;
			}
		}
		conflicts = true;
		workspace_data->grid[random[0]][random[1]] = 'g';
		if( i == 0)
		{
			objects->gold1_xy[0]=random[0];
			objects->gold1_xy[1]=random[1];
		}
		if( i == 1)
		{
			objects->gold2_xy[0]=random[0];
			objects->gold2_xy[1]=random[1];
		}
	}
}

void randomRobot(thread_data *thread, struct workspace *workspace_data);
void randomRobot(thread_data *thread, struct workspace *workspace_data )
{
	int random [2];
	bool conflicts = true;

	while(conflicts == true)
	{
		for(int i =0; i<2;i++)
		{
			random[i] = getRandom(0,3);
		}
		if(workspace_data->grid[random[0]][random[1]] != 'b' && workspace_data->grid[random[0]][random[1]] != 'g')
		{
			conflicts = false;
		}
	}
	workspace_data->grid[random[0]][random[1]] = 'r';

	//1 for robot
	thread[1].cord_xy[0]=random[0];
	thread[1].cord_xy[1]=random[1];

}


void is_gold(thread_data *thread);
void is_gold(thread_data *thread)
{
		if((thread->the_objects->gold1_xy[0] == thread->cord_xy[0] && thread->the_objects->gold1_xy[1] == thread->cord_xy[1])&& thread->the_objects->gold1_found == 0)
		{
			printf("gold found at %d,%d \n",thread->cord_xy[0],thread->cord_xy[1]);
			thread->the_objects->gold1_found = 1;
		}
		if((thread->the_objects->gold2_xy[0] == thread->cord_xy[0] && thread->the_objects->gold2_xy[1] == thread->cord_xy[1])&& thread->the_objects->gold2_found == 0)
		{
			printf("gold found at %d,%d \n",thread->cord_xy[0],thread->cord_xy[1]);
			thread->the_objects->gold2_found = 1;
		}
}

bool is_still_gold(struct objects *object);
bool is_still_gold(struct objects *object)
{
	if(object->gold1_found == 0 || object->gold2_found == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void move_robot(thread_data *objects);
void move_robot(thread_data *objects){

	//todo move robot around switch statements
	// use 0-7 random numbers so we know where to move robot
	// 765
	// 4R3
	// 210

	// generate random num move to corresponding spot relative to R
	// check to see if spot is valid else loop back
	// implementing now 4:14 pm 9/6

	pthread_mutex_lock(&thread_mutex);
	int xcord = 0;
	int ycord = 0;
	static int ROBOT_STEPS = 0;
	int random_number = 0;
	while(1){
//*** Error in `./gold_bomb': double free or corruption (!prev): 0x000000000097c010 ***


		//scanf("%d", &random_number);
                random_number = getRandom(0,7);
                xcord = objects->cord_xy[1];
                ycord = objects->cord_xy[0];

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

		//debug
		//printf("here\n");
	       	if((xcord >= 0 && xcord <= 3) && (ycord >= 0 && ycord <= 3)){

        	                if(objects->the_grid->grid[ycord][xcord] != 'b' && (ROBOT_STEPS <2) && objects->thread_num == 1){

					objects->the_grid->grid[objects->cord_xy[0]][objects->cord_xy[1]] = '-';
        	                        objects->the_grid->grid[ycord][xcord] = 'R';

					objects->cord_xy[1] = xcord;
	                                objects->cord_xy[0] = ycord;
					ROBOT_STEPS ++;
	                                break;

	                        }else if(objects->the_grid->grid[ycord][xcord] != 'R' && objects->thread_num == 0 && objects->the_grid->grid[ycord][xcord] != 'g'){

					objects->the_grid->grid[objects->cord_xy[0]][objects->cord_xy[1]] = '-';
					objects->the_grid->grid[ycord][xcord] = 'b';

					objects->cord_xy[1] = xcord;
					objects->cord_xy[0] = ycord;
					ROBOT_STEPS = 0;
					break;
				}else{
	                                xcord = objects->cord_xy[1];
	                                ycord = objects->cord_xy[0];
	                        }
		}else{

			xcord = objects->cord_xy[1];
	                ycord = objects->cord_xy[0];
	        }


	}

	printf("%d = robot steps for thread %d \n", ROBOT_STEPS, objects->thread_num);
        printf("xcord = %d and ycord = %d \n", xcord, ycord);
        print_grid(objects->the_grid);

	pthread_mutex_unlock(&thread_mutex);
}


void make_workspace(thread_data *thread, struct workspace *workspace_data, struct objects *objects);
void make_workspace(thread_data *thread, struct workspace *workspace_data, struct objects *objects){

	for(int i=0; i<4; i++){

		for(int j=0; j<4; j++){

			workspace_data->grid[i][j] = '-';
		}
	}

	randomBomb(thread, workspace_data);
	randomGold(workspace_data,objects);
	randomRobot(thread, workspace_data);
	print_grid(workspace_data);
}

void init(thread_data *thread, struct objects *objects, struct workspace *grid);
void init(thread_data *thread, struct objects *objects, struct workspace *grid){

	thread[0].the_objects = objects;
	thread[0].the_grid    = grid;
	thread[1].the_objects = objects;
	thread[1].the_grid    = grid;

	print_grid(thread->the_grid);
}

void *API(void *thread){

	thread_data *objects = (thread_data*)thread;

	while(is_still_gold(objects->the_objects) == 1){

		move_robot(objects);
		is_gold(objects);
		sleep(2);


	}

}

//function: main
int main(int argc, char* argv[])
{

	thread_data      thread[2];
	struct workspace *grid;
	struct objects   *object;
	struct timeval   time;

	//----------------------------------------------
	gettimeofday(&time, NULL);
	srandom((unsigned int) time.tv_usec);

	//----------------------------------------------
	grid   = malloc(250);
	object = malloc(250);
	//thread->the_grid = malloc(250);
	//thread->the_object = malloc(250);
	//----------------------------------------------
	printf("here we go \n");

	object->gold1_found = false;
	object->gold2_found = false;

	make_workspace(thread, grid, object);
	init(thread, object, grid);

	pthread_mutex_init(&thread_mutex, NULL);

	for(int i=0; i<2; i++){

		thread[i].thread_num = i;
		pthread_create(&(thread[i].thread_id), NULL, API, (void *)(&thread[i]));
	}

	for(int i=0; i<2; i++){

		pthread_join(thread[i].thread_id, NULL);
	}

	pthread_mutex_destroy(&thread_mutex);

	printf("All gold found, terminating \n");
	free(object);
	free(grid);
	//free(thread->the_grid);
	return 0;
}
