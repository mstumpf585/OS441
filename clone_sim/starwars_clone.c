#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct data_clone{

	int ID;
	char name[30];
	int timeCounter;

};

int  create_clone(struct data_clone *clone);
void input(struct data_clone *clone, int user_size);
void life_span(struct data_clone *clone);

int create_clone(struct data_clone *clone){

	int user_size = 0;
        scanf("%d", &user_size);
        clone = (struct data_clone*) malloc(user_size*sizeof(struct data_clone));

	if(clone == NULL){

		printf("not enough mem");
		exit(1);
	}else{

		printf("worked \n");
	}

	return user_size;
}

void input(struct  data_clone *clone, int user_size){

	char temp_name[30];
	int c;
	int temp;

	printf("Clone name: \n");

	for(int i; i<user_size; i++){

		scanf("enter ID %d", &temp);
		clone[i].ID = temp;

		while((c = fgetc(stdin)) != EOF && c != '\n');
		fgets(clone->name, 30, stdin);
		sscanf(clone->name,"%s",&temp_name);

		temp = 0;
		scanf("enter life span %d", &temp);
		clone[i].timeCounter = temp;
	}
}

int main(int argc, char* argv[]){

	struct data_clone *Aclone;

	int temp_num;

	temp_num = create_clone(Aclone);
	input(Aclone, temp_num);
}
