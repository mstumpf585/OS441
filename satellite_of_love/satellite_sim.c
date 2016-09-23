#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
//kevin was here haha
#define term_count 10
#define channels 2
#define array_size 5

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
	int que_num[2];

	if(sizeof(que->waiting_countries) !=0){

		que_num[0] = 0;

		if (sizeof(que->waiting_countries != 0)){

			que_num[1] = 1;
		}
	}else{

		// well thats all folks
		return;
	}

	data_channel *channel;
	channel = (data_channel*) malloc(channels*sizeof(data_channel));

	struct timeval time;
        gettimeofday(&time,NULL);
        srandom((unsigned int) time.tv_usec);

	// should this be random ????
	channel[0].countDown = random_min_max(1,10) + 1;
	channel[1].countDown = random_min_max(1,10) + 1;

	strcpy(channel[1].country, country[que->waiting_countries[que_num[0]]]->name);
	strcpy(channel[2].country, country[que->waiting_countries[que_num[1]]]->name);

	while(1){

		hour++;

		for(int i=0; i<channels; i++){

			channel[i].countDown--;

			printf("%d till death\n", channel[i].countDown);

			if(channel[i].countDown <= 0){

				printf("loading new country\n");

				if(que_num[i] + 1 <= sizeof(que->waiting_countries)){

					printf("in the other thing\n");
					que_num[i] ++;
					strcpy(channel[i].country, country[que->waiting_countries[que_num[i]]]->name);

					gettimeofday(&time,NULL);
					srandom((unsigned int) time.tv_usec);
					channel[i].countDown = random_min_max(1,10)+1;

				}else{

					if(que_num[i+1] + 1 > sizeof(que->waiting_countries)){

						return;
					}else{

					}

				}
			}
		}

		printf("transmitting for %s and %s\n",channel[1].country, channel[2].country);
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

		printf("%d is the pack for %s\n",country[que->waiting_countries[i]]->selectedPack, country[que->waiting_countries[i]]->name);
	}

	function_canTake(country, canTake,array_size);
	transmit(country, canTake,que,array_size);
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
	canTake = (data_canTake*) malloc(array_size*sizeof(data_canTake));

	strcpy(country[0]->name, "USA");
	strcpy(country[1]->name, "China");
	strcpy(country[2]->name, "Germany");
	strcpy(country[3]->name, "Japan");
	strcpy(country[4]->name, "Switzerland");

	API(country, canTake, que, array_size);

	free(que);
	for(int i=0; i<array_size; i++){
		free(country[i]);
	}
}
