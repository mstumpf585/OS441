#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct data_clone{

	int clone_ID;
	char name[30];
	int timeCounter;
};

int  create_clone(struct data_clone *clone);
void input(struct data_clone *clone, int user_size);
void life_span(struct data_clone *clone, int user_size);

void life_span(struct data_clone *clone, int user_size){

	int break_flag = 0;

	while(1){

		for(int i=0; i<user_size; i++){

			if(clone[i].timeCounter > 0){

				break_flag++;

				printf("clone ID: %d \n", clone[i].clone_ID);
				printf("clone Name: %s", clone[i].name);
				printf("clone Life Span %d \n\n", clone[i].timeCounter);

				clone[i].timeCounter--;
			}else{


				printf("%sis dead\n\n",clone[i].name);
			}
		}
		if(break_flag != 0){

			break_flag = 0;
		}else{

			break;
		}
	}



}
void input(struct  data_clone *clone, int user_size){

        char temp_name[30];
        int c;
        int temp;

	printf("in input user size is %d \n", user_size);
	for(int i=0; i<user_size; i++){

		printf("enter clone ID: ");
		scanf("%d", &temp);
		clone[i].clone_ID = temp;

		printf("enter clone name: ");
		while((c = fgetc(stdin)) != EOF && c != '\n');
		fgets(clone[i].name, 30, stdin);
		sscanf(clone[i].name,"%s",&temp_name);

		temp = 0;

		printf("enter lifespan: ");
		scanf("%d", &temp);
		clone[i].timeCounter = temp;

		printf("\n");
        }
}

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

	input(clone, user_size);
	life_span(clone,user_size);
	return user_size;
}

int main(int argc, char* argv[]){

	struct data_clone *Aclone;
	int temp_num;

	temp_num = create_clone(Aclone);
}
