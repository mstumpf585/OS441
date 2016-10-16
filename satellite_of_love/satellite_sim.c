#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define term_count 10
#define channels 2
#define array_size 5

typedef struct{
	char name[30];
	int  active;
	int  selectedPack;
}data_country;

typedef struct{
	int  waiting_countries[5];
}data_queue;

typedef struct{
	int countDown;
	char country[30];

}data_channel;

int  random_min_max(int rangeLow, int rangeHigh);

void transmit(data_country *country[], data_queue *que,
	int total_countries);

void API(data_country *country[], data_queue *que,
        int total_countries);


int random_min_max(int rangeLow, int rangeHigh){

	double myRand = rand()/(1.0 + RAND_MAX);
	int range = rangeHigh - rangeLow + 1;
	int myRand_scaled = (myRand * range) + rangeLow;
	return myRand_scaled;
}

int get_countDown(int selected_pack){

	switch (selected_pack){

		case 1:
			return 1;

		case 2:
			return 3;

		case 3:
			return 5;

		case 4:
			return 10;

	}

}

int get_cash(int selected_pack){

	switch(selected_pack){

		case 1:
			return 210;

		case 2:
			return 350;

		case 3:
			return 400;

		case 4:
			return 500;
	}

}

void transmit(data_country *country[], data_queue *que,
	int total_countries){

	int hour = 0;
	int que_num[2];
	int total_profit = 0;

	if(total_countries != 0){

		que_num[0] = 0;

		if (total_countries > 1){

			que_num[1] = 1;
		}
	}else{
		que_num[1] = 9999;
	}


	data_channel *channel;
	channel = (data_channel*) malloc(channels*sizeof(data_channel));

	struct timeval time;
        gettimeofday(&time,NULL);
        srandom((unsigned int) time.tv_usec);

	channel[0].countDown = get_countDown(country[que->waiting_countries[que_num[0]]]->selectedPack);
	channel[1].countDown = get_countDown(country[que->waiting_countries[que_num[1]]]->selectedPack);

	strcpy(channel[0].country, country[que->waiting_countries[que_num[0]]]->name);
	strcpy(channel[1].country, country[que->waiting_countries[que_num[1]]]->name);

	while(1){

		hour++;

		if(que_num[0] == 9999 && que_num[1] == 9999){

			printf("No more countries profit == $%d \ntotal hours == %d \n",total_profit, hour);
			free(channel);
			return;
		}

		for(int i=0; i<channels; i++){

			channel[i].countDown--;

			printf("%d till death\n", channel[i].countDown);

			if(channel[i].countDown <= 0){

				if(que_num[0] != total_countries-1 && que_num[1] != total_countries-1){


					que_num[i] ++;

					printf("loading %s into channel %d \n",country[que->waiting_countries[que_num[i]]]->name, i);

					strcpy(channel[i].country, country[que->waiting_countries[que_num[i]]]->name);

					gettimeofday(&time,NULL);
					srandom((unsigned int) time.tv_usec);
					channel[i].countDown = random_min_max(1,10)+1;

					total_profit += get_cash(country[que->waiting_countries[que_num[i]]]->selectedPack) * hour;
					printf("total profit so far is $%d \n", total_profit);

				}else{
					que_num[i] = 9999;
					strcpy(channel[i].country,"none");

					total_profit += get_cash(country[que->waiting_countries[que_num[i]]]->selectedPack) * hour;
                                        printf("total profit so far is $%d \n", total_profit);

					if(que_num[i+1] + 1 > total_countries){

						printf("returning \n");
						printf("No more countries profit == $%d \ntotal hours == %d \n",total_profit, hour);

						return;
					}

				}
			}
		}

			printf("transmitting for %s and %s\n",channel[0].country, channel[1].country);
	}

}

void API(data_country *country[], data_queue *que,
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

	if(que_count == 0){return;}
        for(int i=0; i<que_count; i++){

                printf("%d is the pack for %s\n",country[que->waiting_countries[i]]->selectedPack, country[que->waiting_countries[i]]->name);
        }

	transmit(country, que, que_count);
}

int main(int argc, char* argv[]){

	data_country *country[5];
	data_queue   *que;

	for(int i=0; i<5; i++){

		country[i] = malloc(30);
		country[i]->active = 0;
	}

	que = malloc(4);

	strcpy(country[0]->name, "USA");
	strcpy(country[1]->name, "China");
	strcpy(country[2]->name, "Germany");
	strcpy(country[3]->name, "Japan");
	strcpy(country[4]->name, "Switzerland");

	API(country, que, array_size);

	free(que);
	for(int i=0; i<array_size; i++){
		free(country[i]);
	}
}
