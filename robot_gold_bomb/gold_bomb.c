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

void make_workspace(struct workspace *workspace_data);
void make_workspace(struct workspace *workspace_data){

	for(int i=0; i<4; i++){

		for(int j=0; j<4; j++){

			workspace_data->grid[i][j] = '-';
		}
	}

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
