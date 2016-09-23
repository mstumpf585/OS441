using namespace std;

#include <iostream>
#include <string>
#include <time.h>

typedef struct country {
	string name;
	int active;
	int selectedPack;
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
	transmit(country, canTake, queue, global_queue);

	cout << "Total Cost " << global_cost << endl;
	cout << "Total Time " << global_time << "hours" << endl;
	cout << "Entering Maintenence Mode" << endl;
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

	//assigns times based off of package selected
	channel[0].countDown = transmit_time(country[queue->waiting_countries[que_num[0]]].selectedPack);
	channel[0].country = country[queue->waiting_countries[que_num[0]]].name;
	//if there is only one country, doing this would throw an out of bounds error
	if (total_countries != 1)
	{
		channel[1].countDown = transmit_time(country[queue->waiting_countries[que_num[1]]].selectedPack);
		channel[1].country = country[queue->waiting_countries[que_num[1]]].name;
	}

	while (loop){
		for (int i = 0; i < CHANNELS; i++){
			//checks to see if both countDowns are 0 so we don not infinitely loop
			if (channel[0].countDown == 0 && channel[1].countDown == 0){
				cout << "both halves have completed" << endl;
				loop = false;
			}
			//checks to see if the current channel is 0 so we don't get an array access error
			if (channel[i].countDown != 0)
			{
				//decrements count
				channel[i].countDown--;
				//keeps track of overall time we spent sending transmissions
				global_time++;
				//gives status update to the user
				cout << channel[i].country << " " << channel[i].countDown << " hours till Completition" << endl;
				//if the channel's count has just hit 0 we need to change countries
				if (channel[i].countDown <= 0){
					//inform the user how long and how much that country cost
					cout << channel[i].country << " took " << transmit_time(country[queue->waiting_countries[que_num[i]]].selectedPack) << " hour and cost " << transit_cost(country[queue->waiting_countries[que_num[i]]].selectedPack) << endl;
					//checks to make sure que_num[i] will be in bounds and that we have two countries, otherwise no reason to change countries
					if (que_num[i] + 1 <= total_countries && total_countries !=1){
						cout << "In change Countries" << endl; 

						//somewhere below here we get an error of trying to access an element ouside of an array and it crashes sometimes, not super consistently


						que_num[i] ++;
						//checks if que_num[i] is still in the valid range of countries
						if (que_num[i] < total_countries){
							//checks to see if the channels would have duplicate information placed into them
							if (country[queue->waiting_countries[que_num[0]]].name == country[queue->waiting_countries[que_num[1]]].name)
							{
								//if the channels would ahve duplicate information placed into them we increment que_num[i] by one more to avoid conflict
								que_num[i]++;
								cout << "skipped to next country" << endl;
							}
							//informs us that we have successfully changed countries
							cout << "successfully changed countries" << endl;
							//puts the name of the new current country into the channel
							channel[i].country = country[queue->waiting_countries[que_num[i]]].name;
							//assigns the next transmission time based off the packagge that was selected by that country
							channel[i].countDown = transmit_time(country[queue->waiting_countries[que_num[i]]].selectedPack);
						}

					}
					else{
						channel[i].country = "none";
						if (que_num[i + 1] + 1 > sizeof(queue->waiting_countries)){
							loop = false;
						}
					}
				}
				if (total_countries == 1){ i++; }
			}
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
			if (country[i].active == 1){
				queue->waiting_countries[queue_count] = i;
				queue_count++;
			}
		}
	}

	//test
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