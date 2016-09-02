/*
 * heli.c
 *
 *  Created on: Aug 25, 2016
 *      Author: michael
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct flying_data{

		int rockets[4];
		int visibility;
		double fuel;
		char *pilot_name;
};

//  function: weather_input
//  inputs: flying_data pointer
//  returns: none
void weather_input(struct flying_data *myHelicopter);
void weather_input(struct flying_data *myHelicopter){

	int current_visibility;
	printf("enter current visibility: ");

	// get visibility from user
	scanf("%d", &current_visibility);
	myHelicopter->visibility = current_visibility;
}

// function: fill_tank
// inputs: flying_data pointer
// returns: none
void fill_tank(struct flying_data *myHelicopter);
void fill_tank(struct flying_data *myHelicopter){

	double bars;
	printf("enter the number of fuel bars: ");

	// get fuel from user
	scanf("%lf", &bars);
	myHelicopter->fuel = bars;
}

// shoot_rockets
// input: flying_data pointer
// returns: none
void shoot_rockets(struct flying_data *myHelicopter);
void shoot_rockets(struct flying_data *myHelicopter){

	// check to see if any rockets are loaded if so fire!
	for(int i =0; i< 4; i++){

		// check to see if any rocets are left
		if(myHelicopter->rockets[0] == 0 
			&& myHelicopter->rockets[1] == 0
			&& myHelicopter->rockets[2] == 0
			&& myHelicopter->rockets[3] == 0 ){

			printf("out of rockets\n");
			break;
		}

		if(myHelicopter->rockets[i] == 1){

			// get rid of the next rocket
			myHelicopter->rockets[i]=0;
			break;
		}
	}
}

// function: fly_helicopter
// input: flying_data pointer array, int
// returns: none
void fly_helicopter(struct flying_data *myHelicopter[], int num_helis);
void fly_helicopter(struct flying_data *myHelicopter[], int num_helis){

	int good_flag[3]    = {0,0,0};    // to keep track of conditions
	double init_fuel[3] = {0,0,0};	  // need this to know when to fire rockets

	int while_counter   = 0;          // to keep track of while loop iterations
	int while_count_mod = 3;	  // how I check when to fire rockets
	double fuel_reduction   = 0;      // to reduce fuel after each loop
	double reduction_factor = .03;    // factor by which we reducde fuel by

	// get initial fuel values
	init_fuel[0] = myHelicopter[0]->fuel;
	init_fuel[1] = myHelicopter[1]->fuel;
	init_fuel[2] = myHelicopter[2]->fuel;

	// tell user where we are at
	printf("checking flight conditions \n\n");

	// go through and check flight conditions for each choper
	for(int i=0; i<num_helis; i++){

		// identify choper by pilot
		printf("%s's information: \n", myHelicopter[i]->pilot_name);

		// check weather
		if(myHelicopter[i]->visibility < 60){

			printf("visibility below 60 percent: bad \n");
			good_flag[i] = 1;
		}else{

			printf("visibility: good \n");
		}

		// check fuel
		if(myHelicopter[i]->fuel < 1){
			printf("fuel at 10 percent: bad \n\n");
			good_flag[i] = 1;
		}else{

			printf("fuel above 10 percent: good \n\n");
		}

		//load rockets
		for(int j=0; j<4; j++){

			myHelicopter[i]->rockets[j] = 1; 
		}

		// if you dont do this the loop will never end
		// check num helis and change the flag of the third
		if(num_helis == 2){
			good_flag[2] = 1;
		}
	}

	// start flight for helicopters with good conditions
	for(int i=0; i<num_helis; i++){

		if(good_flag[i] == 0){

			printf("flight conditions are good for %s ... helicopter taking off \n\n", myHelicopter[i]->pilot_name);
		}else{

			printf("flight conditions are bad for %s ... helicopter grounded \n\n", myHelicopter[i]->pilot_name);
		}
	}

	// main loop for flying the choppers
	while(1){

		// go through and check each flag
		for(int i=0; i<num_helis; i++){

			// if the flag is 1 print that it is still in air and fuel
			if(good_flag[i] == 0){

				printf("%s's helicopter still in air ", myHelicopter[i]->pilot_name);
				printf("fuel level %f.\n", myHelicopter[i]->fuel);

				// reduce fuel by 3%
				myHelicopter[i]->fuel = myHelicopter[i]->fuel - (myHelicopter[i]->fuel * reduction_factor);

				// check fuel again
				if(myHelicopter[i]->fuel <= 1.0){

					good_flag[i] = 1;
				}

				// every third loop fire rocket
				if(while_counter % while_count_mod == 0 &&
					myHelicopter[i]->fuel <= init_fuel[i]/2.0){

					printf("firing rockets!! \n\n");
					shoot_rockets(myHelicopter[i]);
				}

			}
		}

		// clean up output
		printf("\n");

		// if all flags are bad end it
		if(good_flag[0] == 1 && good_flag[1] == 1 && good_flag[2] == 1){

			printf("all helicopters have landed we out here \n");
			break;
		}

		while_counter++;
	}
}

//function: API
//input: flying_data pointer array, int
//returns: none
void API(struct flying_data *myHelicopter[], int num_helis);
void API(struct flying_data *myHelicopter[], int num_helis){

	// intiate flight
	for(int i=0; i<num_helis; i++){

		printf("information for ");
	        printf("%s", myHelicopter[i]->pilot_name); 
		printf( ": \n");
		weather_input(myHelicopter[i]);
		fill_tank(myHelicopter[i]);
		printf("\n");
	}

	fly_helicopter(myHelicopter, num_helis); 

}

//function: main
int main(int argc, char* argv[])
{
	int number_of_helicopters;
	int good_bad = 0;
	char *name;

	while(1){

		// get number of helicopters to fly
		printf("enter the number of helicopters either 2 or 3: ");
		good_bad = scanf("%d", &number_of_helicopters);

		if(number_of_helicopters > 3 || number_of_helicopters < 2 || good_bad != 1){
			printf("the number has to be either 2 or 3 \n");
		}else{
			break;
		}
	}

	struct flying_data *choppers[3];
	printf("%d \n", number_of_helicopters);
	// get names for each pilot
	for(int i=0; i < number_of_helicopters; i++){

		// get names of pilots
		printf("enter pilot %d name: ", i);

		// allocate space for name
		name = malloc(250);
		scanf("%s", name);

		// allocate space for pilot name
		choppers[i] = malloc(250);
		choppers[i]->pilot_name = malloc(250);
		if(choppers[i]->pilot_name == NULL){
			printf("well there is not enough memory");
		}
		printf("\n");

		strcpy(choppers[i]->pilot_name, name);
		free(name);
	}

	API(choppers, number_of_helicopters);
	free(choppers[0]);
	free(choppers[1]);
	free(choppers[2]);
}


