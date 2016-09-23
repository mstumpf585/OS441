#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define term_count 10

typedef struct{
	char name[30];
	int  active;
	int  selectedPack;
}data_country;

typedef struct{
	int available;
}data_canTake;

typedef struct{
	int  waiting_countries[5];
}data_queue;

typedef struct{
	int countDown;
	char country[30];

}data_channel;

void function_canTake(data_country *country[], data_canTake *canTake,
        int total_countries);

int  random_min_max(int rangeLow, int rangeHigh);

void transmit(data_country *country[], data_canTake *canTake, data_queue *que,
	int total_countries);

void API(data_country *country[], data_canTake *canTake, data_queue *que,
        int total_countries);



void function_canTake(data_country *country[], data_canTake *canTake,
	int total_countries){

	for(int i=0; i<total_countries; i++){

		if(country[i]->active){
			canTake[i].available = country[i]->active;
		}else{

			canTake[i].available= (int)0;
		}
	}

}

int random_min_max(int rangeLow, int rangeHigh){

	double myRand = rand()/(1.0 + RAND_MAX);
	int range = rangeHigh - rangeLow + 1;
	int myRand_scaled = (myRand * range) + rangeLow;
	return myRand_scaled;
}

void transmit(data_country *country[], data_canTake *canTake, data_queue *que,
	int total_countries){

	// change
	int hour = 0;
	int que_pointer  = 0;
	int que_pointer2 = 1;

	data_channel *channel1;
	data_channel *channel2;

	channel1 = malloc(40);
	channel2 = malloc(40);

	// should this be random ????
	channel1->countDown = term_count;
	channel2->countDown = term_count;

	//condition for this while loops should be while transmissionis remaining
	while(1){

		hour++

		//will have to grab up two elements from queue
		//decrement them based on time that it takes transmit their payload
		//whenever a channel is empty, new country from queue will be loaded in


		// mike doesn't know what to do here either 
		// git is weird

	}

}

void API(data_country *country[], data_canTake *canTake, data_queue *que,
     	int total_countries){

	int que_count = 0;

	for(int i=0; i<total_countries; i++){

		struct timeval time;
		gettimeofday(&time,NULL);
		srandom((unsigned int) time.tv_usec);

		if(country[i]->active == 0){

			country[i]->active = random_min_max(0,1);
			country[i]->selectedPack = random_min_max(0,3)+1;
			if(country[i]->active == 1){
				que->waiting_countries[que_count] = i;
				que_count++;
			}
		}
	}

	//test
	//for(int i=0; i<que_count; i++){
		//printf("package %d \n",country[i]->selectedPack); 
		//printf("%d \n", que->waiting_countries[i]);
		//printf("%s selected pack %d \n",country[que->waiting_countries[i]]->name,country[que->waiting_countries[i]]->selectedPack);
	//}
}

int main(int argc, char* argv[]){

	data_country *country[5];
	data_queue   *que;
	data_canTake *canTake;

	for(int i=0; i<5; i++){

		country[i] = malloc(30);
		country[i]->active = 0;
	}

	que = malloc(4);
	canTake = (data_canTake*) malloc(5*sizeof(data_canTake));

	strcpy(country[0]->name, "USA");
	strcpy(country[1]->name, "China");
	strcpy(country[2]->name, "Germany");
	strcpy(country[3]->name, "Japan");
	strcpy(country[4]->name, "Switzerland");

	API(country, canTake, que, 5);



	free(que);
	for(int i=0; i<5; i++){
		free(country[i]);
	}
}
