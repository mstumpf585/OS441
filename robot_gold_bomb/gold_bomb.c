/*
 * gold_bomb.c
 *
 *  Created on: Sep 1, 2016
 *      Author: michael
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct workspace{
	 char grid[4][4];
};

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

void randomBomb(struct workspace *workspace_data);
void randomBomb(struct workspace *workspace_data)
{
	int random [2];
	for(int i =0; i<2;i++)
	{
		random[i] = getRandom(0,3);
	}
	workspace_data->grid[random[0]][random[1]] = 'b';
}

void randomGold(struct workspace *workspace_data);
void randomGold(struct workspace *workspace_data)
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
		workspace_data->grid[random[0]][random[1]] = 'g';
	}
}

void randomRobot(struct workspace *workspace_data);
void randomRobot(struct workspace *workspace_data)
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

}

void make_workspace(struct workspace *workspace_data);
void make_workspace(struct workspace *workspace_data){

	for(int i=0; i<4; i++){

		for(int j=0; j<4; j++){

			workspace_data->grid[i][j] = '-';
		}
	}

	randomBomb(workspace_data);
	randomGold(workspace_data);
	randomRobot(workspace_data);
	print_grid(workspace_data);

}



//function: main
int main(int argc, char* argv[])
{

	struct workspace *tester;
	tester = malloc(250);
	printf("here we go \n");

	make_workspace(tester);
	free(tester);
}
