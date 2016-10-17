using namespace std;

#include <iostream>
#include <string>
#include <time.h>

typedef struct country {
	string name;
	int active;
	int selectedPack;
	bool has_tansmitted;
}data_country;

typedef struct queue {
	int waiting_countries[5];
}data_queue;

typedef struct{
	int countDown;
	string country;

}data_channel;

typedef struct{
	int available;
}data_canTake;

#define NUM_COUNTRIES 5
#define CHANNELS 2

void API(data_country *country, data_queue *queue);
void transmit(data_country *country, data_canTake *canTake, data_queue *queue, int total_countries);
void function_canTake(data_country *country, data_canTake *canTake, int total_countries);
int transmit_time(int plan);
int transit_cost(int time);

//possibly bad global variables, also it was like 130am whenever i put these in
int global_queue = 0;
int global_cost = 0;
int global_time = 0;

int main()
{
	data_country *country;
	country = new data_country[5];
	data_queue *queue = new data_queue;
	data_canTake *canTake = new data_canTake;

	for (int i = 0; i < NUM_COUNTRIES; i++)
	{
		country[i].active = 0;
	}

	country[0].name = "USA";
	country[1].name = "China";
	country[2].name = "Germany";
	country[3].name = "Japan";
	country[4].name = "Switzerland";

	API(country, queue);
	if (global_queue != 0){
	transmit(country, canTake, queue, global_queue);

	cout << "Total Cost " << global_cost << endl;
	cout << "Total Time " << global_time << " hours" << endl;
	cout << "Entering Maintenence Mode" << endl;
	}

	if (global_queue == 0)
	{
		cout << "No countries want to transmit" <<  endl;
	}
}

int transmit_time(int plan)
{
	switch (plan){
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

int transit_cost(int plan)
{
	switch (plan){
	case 1:
		global_cost += 210;
		return 210;
	case 2:
		global_cost += 350;
		return 350;
	case 3:
		global_cost += 400;
		return 400;
	case 4:
		global_cost += 500;
		return 500;
	}

}

void transmit(data_country *country, data_canTake *canTake, data_queue *queue, int total_countries)
{
	int que_num[2];
	bool loop = true;

	if (total_countries != 0){

		que_num[0] = 0;

		if (total_countries > 1){

			que_num[1] = 1;
		}
	}
	else{
		loop = false;
	}

	data_channel *channel;
	channel = new data_channel[2];

	channel[0].countDown = transmit_time(country[queue->waiting_countries[que_num[0]]].selectedPack);
	channel[0].country = country[queue->waiting_countries[que_num[0]]].name;
	country[queue->waiting_countries[que_num[0]]].has_tansmitted = true;
	if (total_countries != 1)
	{
		channel[1].countDown = transmit_time(country[queue->waiting_countries[que_num[1]]].selectedPack);
		channel[1].country = country[queue->waiting_countries[que_num[1]]].name;
		country[queue->waiting_countries[que_num[1]]].has_tansmitted = true;
	}
	if (global_queue == 1){
		channel[1].country = "none";
		channel[1].countDown = 0;
	}
	bool has_counted = false;
	while (loop){
		for (int i = 0; i < CHANNELS; i++){
			if (channel[0].countDown == 0 && channel[1].countDown == 0){
				loop = false;
			}
			if (channel[i].countDown != 0)
			{
				has_counted = true;
				channel[i].countDown--;
				cout << channel[i].country << " " << channel[i].countDown << " hours till Completition, channel " << i<<endl;
				if (channel[i].countDown == 0){
					cout << channel[i].country << " took " << transmit_time(country[queue->waiting_countries[que_num[i]]].selectedPack) << " hour(s) and cost " << transit_cost(country[queue->waiting_countries[que_num[i]]].selectedPack) << endl;
					if (que_num[i] <= global_queue - 1 && total_countries != 1){
						while (country[queue->waiting_countries[que_num[i]]].has_tansmitted)
						{
							if (que_num[i] + 1 > global_queue-1){
								channel[i].country = "none";
								channel[i].countDown = 0;
								break;
							}
							que_num[i]++;
						}
						
						if (que_num[i] <= global_queue - 1 && channel[i].country != "none"){
								cout << "successfully changed countries in channel " << i << endl;
								channel[i].country = country[queue->waiting_countries[que_num[i]]].name;
								channel[i].countDown = transmit_time(country[queue->waiting_countries[que_num[i]]].selectedPack);
								country[queue->waiting_countries[que_num[i]]].has_tansmitted = true;
						}

					}
				}
				if (total_countries == 1){ i++; }
			}
		}
		if (has_counted)
		{
			global_time++;
			has_counted == false;
		}
	}

}


void API(data_country *country, data_queue *queue)
{
	int queue_count = 0;
	srand(time(NULL));
	for (int i = 0; i < NUM_COUNTRIES; i++){
		if (country[i].active == 0){
			country[i].active = rand() % 2;
			country[i].selectedPack = rand() % 4 + 1;
			country[i].has_tansmitted = false;
			if (country[i].active == 1){
				queue->waiting_countries[queue_count] = i;
				queue_count++;
			}
		}
	}
	for (int i = 0; i < queue_count; i++){
		cout << country[queue->waiting_countries[i]].name << " selected pack " << country[queue->waiting_countries[i]].selectedPack << endl;
	}

	global_queue = queue_count;
}

void function_canTake(data_country *country, data_canTake *canTake, int total_countries){

	for (int i = 0; i < total_countries; i++){
		if (country[i].active){
			canTake[i].available = country[i].active;
		}
		else{
			canTake[i].available = (int)0;
		}
	}

}