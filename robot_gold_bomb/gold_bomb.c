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

struct workspace{
	 char grid[4][4];
};

struct objects{

	int robot_xy[2];
	int bomb_xy[2];
	int gold1_xy[2];
	bool gold1_found = false;
	int gold2_xy[2];
	bool gold2_found = false;
};

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

void randomBomb(struct workspace *workspace_data, struct objects *objects);
void randomBomb(struct workspace *workspace_data, struct objects *objects)
{
	int random [2];
	for(int i =0; i<2;i++)
	{
		random[i] = getRandom(0,3);
	}
	workspace_data->grid[random[0]][random[1]] = 'b';
	objects->bomb_xy[0]=random[0];
	objects->bomb_xy[1]=random[1];
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

void randomRobot(struct workspace *workspace_data, struct objects *objects);
void randomRobot(struct workspace *workspace_data, struct objects *objects)
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
	objects->robot_xy[0]=random[0];
	objects->robot_xy[1]=random[1];

}


void check_gold(struct object *object,struct workspace *workspace_data, xcord, ycord);
void check_gold(struct object *object,struct workspace *workspace_data, xcord, ycord)
{
	if((object->gold1_xy[0] == xcord && object->gold1_xy[1] == ycord)||(object->gold2_xy[0] == xcord && object->gold2_xy[1] == ycord))
	{
		printf("gold found at %d,%d ",xcord,ycord);
		workspace_data->grid[xcord][ycord] = '-';
		
		if(object->gold1_xy[0] == xcord && object->gold1_xy[1] == ycord)
		{
			object->gold1_found = true;
		}
		if(object->gold2_xy[0] == xcord && object->gold2_xy[1] == ycord)
		{
			object->gold2_found = true;
		}
		//todo set a flag as gold 1 or gold 2 found 
		//will allow us to use/make function is_still_gold
		
	}
}

bool is_still_gold(struct object *object);
bool is_still_gold(struct object *object)
{
	if(object->gold1_found == false || object->gold2_found == false)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void move_robot(struct workspace *workspace_data, struct objects *objects);
void move_robot(struct workspace *workspace_data, struct objects *objects){

	//todo move robot around switch statements
	// use 0-7 random numbers so we know where to move robot
	// 765
	// 4R3
	// 210

	// generate random num move to corresponding spot relative to R 
	// check to see if spot is valid else loop back
	// implementing now 4:14 pm 9/6

	if(is_still_gold(objects))
	{
	int xcord = 0;
	int ycord = 0;

	int random_number = 0;
	while(1){

		random_number = getRandom(0,7);
		xcord = objects->robot_xy[0];
		ycord = objects->robot_xy[1];

		switch(random_number){

			case 7:
				// up one left one
				xcord -= 1;
				ycord += 1;
				break;

			case 6:
				// up one
				ycord += 1;
				break;

			case 5:
				//up one right one
				xcord += 1;
				ycord += 1;
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
				ycord -= 1;
				break;

			case 1:
				// down
				ycord -= 1;
				break;

			case 0:
				// down right
				xcord += 1;
				ycord -= 1;
				break;
		}

		if(xcord >= 0 && ycord >= 0){

			if(objects->bomb_xy[0] != xcord && objects->bomb_xy[1] != ycord){
				workspace_data->grid[objects->robot_xy[0]][objects->robot_xy[1]] = '-';
				workspace_data->grid[xcord][ycord] = 'R';
				objects->robot_xy[0] = xcord;
				objects->robot_xy[1] = ycord;
				break;

			}
		}
	}

	printf("xcord = %d and ycord = %d \n", xcord, ycord);
	check_gold(objects,workspace_data,xcord,ycord);
	print_grid(workspace_data);
	}
	else{
		printf("All gold found");
	}
}


void make_workspace(struct workspace *workspace_data, struct objects *objects);
void make_workspace(struct workspace *workspace_data, struct objects *objects){

	for(int i=0; i<4; i++){

		for(int j=0; j<4; j++){

			workspace_data->grid[i][j] = '-';
		}
	}

	randomBomb(workspace_data,objects);
	randomGold(workspace_data,objects);
	randomRobot(workspace_data,objects);
	print_grid(workspace_data);
}



//function: main
int main(int argc, char* argv[])
{

	struct workspace *grid;
	struct objects   *object;
	struct timeval time;
	gettimeofday(&time, NULL);

	srandom((unsigned int) time.tv_usec);

	grid = malloc(250);
	object = malloc(250);
	printf("here we go \n");

	make_workspace(grid,object);
	move_robot(grid, object);
	free(grid);
}
