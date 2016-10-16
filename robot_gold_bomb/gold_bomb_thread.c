//one with thread
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

//--------------------------
#define dos 2

//-------------------------
struct workspace{
	 char grid[4][4];
};

typedef struct{

	int  gold1_xy[2];
	int  gold2_xy[2];
	bool gold1_found;
	bool gold2_found;
} gold_info;

typedef struct thread{
	pthread_t thread_id;
	int  robot_xy[2],thread_num;
}thread_objects;

pthread_mutex_t rob_bomb_mutex;

//-----------------------------------------------------------------------------------------
int getRandom(int rangeLow, int rangeHigh);
void print_grid(struct workspace *workspace_data);
void randomBomb(struct workspace *workspace_data,  thread_objects *objects);
void randomGold(struct workspace *workspace_data, gold_info *objects);
void randomRobot(struct workspace *workspace_data, thread_objects *objects);
void is_gold(thread_objects *object, gold_info *gold_object);
void move_robot(struct workspace *workspace_data, thread_objects *objects, gold_info *gObjects);
void make_workspace(struct workspace *workspace_data, thread_objects *objects, gold_info *gold);
bool is_still_gold(gold_info *object);

//-----------------------------------------------------------------------------------------
int getRandom(int rangeLow, int rangeHigh)
{
	double myRand = rand()/(1.0 + RAND_MAX);
	int range = rangeHigh - rangeLow + 1;
	int myRand_scaled = (myRand * range) + rangeLow;
	return myRand_scaled;
}

void print_grid(struct workspace *workspace_data){

	for(int i=0; i<4; i++){

		for(int j=0; j<4; j++){

			printf(" | ");
			printf("%c", workspace_data->grid[i][j]);
		}
		printf(" | \n");
	}

}

void randomGold(struct workspace *workspace_data, gold_info *objects)
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

void randomRobot(struct workspace *workspace_data, thread_objects *objects)
{
	int random [2];
	bool conflicts = true;
	struct timeval time;
	for(int i=0; i<2; i++){

		printf("hello\n");
		gettimeofday(&time, NULL);
		srandom((unsigned int) time.tv_usec);

		conflicts = true;
		while(conflicts == true){
			for(int i =0; i<2;i++)
			{
				random[i] = getRandom(0,3);
			}
			if(workspace_data->grid[random[0]][random[1]] != 'b' && workspace_data->grid[random[0]][random[1]] != 'g' && workspace_data->grid[random[0]][random[1]] != 'r')
			{
				conflicts = false;
			}
			printf("fuck %d\n",random[0]);
		}

		if(i == 0){
			workspace_data->grid[random[0]][random[1]] = 'r';
			objects[i].robot_xy[0] = random[0];
			objects[i].robot_xy[1] = random[1];
		}else{

			workspace_data->grid[random[0]][random[1] ] = 'b';
			objects[i].robot_xy[0] = random[0];
			objects[i].robot_xy[1] = random[1];
		}
	}
}

void is_gold(thread_objects *object, gold_info *gold_object)
{
		if((gold_object->gold1_xy[0] == object->robot_xy[0] && gold_object->gold1_xy[1] == object->robot_xy[1]) && gold_object->gold1_found == 0)
		{
			printf("gold found at %d,%d \n",object->robot_xy[0],object->robot_xy[1]);
			gold_object->gold1_found = 1;
		}
		if((gold_object->gold2_xy[0] == object->robot_xy[0] && gold_object->gold2_xy[1] == object->robot_xy[1]) && gold_object->gold2_found == 0)
		{
			printf("gold found at %d,%d \n",object->robot_xy[0],object->robot_xy[1]);
			gold_object->gold2_found = 1;
		}
}

bool is_still_gold(gold_info *object)
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

void move_robot(struct workspace *workspace_data, thread_objects *objects, gold_info *gObjects){

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
                        if(workspace_data->grid[ycord][xcord] != 'b'){

                                workspace_data->grid[objects->robot_xy[0]][objects->robot_xy[1]] = '-';
                                workspace_data->grid[ycord][xcord] = 'R';
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
        print_grid(workspace_data);
}

void make_workspace(struct workspace *workspace_data, thread_objects *objects, gold_info *gold){

	for(int i=0; i<4; i++){

		for(int j=0; j<4; j++){

			workspace_data->grid[i][j] = '-';
		}
	}

	randomGold(workspace_data, gold);
	randomRobot(workspace_data, objects);
	print_grid(workspace_data);
}

void *API(void *thread, struct workspace *workspace_data, gold_info *gold){

	thread_objects *objects = (thread_objects*) thread;

	pthread_mutex_lock(&rob_bomb_mutex);


		move_robot(workspace_data, objects, gold);
		is_gold(objects, gold);

	pthread_mutex_unlock(&rob_bomb_mutex);
}

//function: main
int main(int argc, char* argv[])
{

	struct workspace *grid;
	struct timeval time;

	thread_objects rob_bomb[dos];
	gold_info *gold_objects_track;

	gettimeofday(&time, NULL);
	srandom((unsigned int) time.tv_usec);

	grid = malloc(250);
	gold_objects_track = malloc(250);

	printf("here we go \n");

	gold_objects_track->gold1_found = false;
	gold_objects_track->gold2_found = false;

	pthread_mutex_init(&rob_bomb_mutex, NULL);

	for(int i=0; i<dos; i++){

		rob_bomb[i].thread_num=i;
		pthread_create(&(rob_bomb[i].thread_id), NULL, API, (void * struct workspace *, gold_info *)(&rob_bomb[i]));
	}
	printf("All gold found, terminating \n");
	//free(object);
	free(grid);
	free(gold_objects_track);
}
