#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char name[30];
	int  active;
	int  selectedPack;
}data_country;

typedef struct{
	int available;
}data_canTake;

typedef struct{
	char country[30];
	int  waiting_coutries[5];
}data_queue;

typedef struct{
	int countDown;
	char country[30];

}data_channel;

void function_canTake(data_country *country, data_canTake *canTake,
        int total_countries);

void function_canTake(data_country *country, data_canTake *canTake,
	int total_countries){

	for(int i=0; i<total_countries; i++){

		if(country[i].active){
			canTake[i].available = country[i].active;
		}else{

			canTake[i].available= (int)0;
		}
	}

}

int main(int argc, char* argv[]){



}
