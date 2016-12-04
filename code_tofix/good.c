/*
 * good.c
 *
 *  Created on: Oct 20, 2016
 *      Author: michael
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// only for windows//
//-----------------//
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif
//-----------------//

#define N 3

typedef struct thread {
     pthread_t thread_id;
     int       thread_num,id;
     int 	   copy_COUNT_GLOBAL;
     char      color[6];
     int       condition;
} ThreadData;

pthread_mutex_t jet_mutex;

int CONDITION_JET ,COUNT_GLOBAL;

void jetFly(ThreadData *jet){
   pthread_mutex_lock(&jet_mutex);

		if(CONDITION_JET== jet->condition){

		    CONDITION_JET = jet->id;

		    COUNT_GLOBAL++;
		    jet->copy_COUNT_GLOBAL = COUNT_GLOBAL;
		    printf("COUNT_GLOBAL = %d jet->color = %s CONDITION_JET = %d\n",
                                             jet->copy_COUNT_GLOBAL,jet->color,CONDITION_JET);
		}
    pthread_mutex_unlock(&jet_mutex);
}

void *fly_API(void *thread)
{
   ThreadData *jet  = (ThreadData*)thread;

   while(COUNT_GLOBAL < 10){

		jetFly(jet);
		sleep(2);
   }

   pthread_exit(NULL);
}

void init_data(ThreadData *jet){

    	COUNT_GLOBAL=0;
	CONDITION_JET=2;

	jet[0].condition=2;
	jet[0].id=0;
	jet[0].copy_COUNT_GLOBAL=COUNT_GLOBAL;
	strcpy(jet[0].color, "green");

	jet[1].id=1;
	jet[1].condition=0;
	jet[1].copy_COUNT_GLOBAL=COUNT_GLOBAL;
	strcpy(jet[1].color, "yellow");

	jet[2].id=2;
	jet[2].condition=1;
	jet[2].copy_COUNT_GLOBAL=COUNT_GLOBAL;
	strcpy(jet[2].color, "red");
}

int main(int argc, char *argv[])
{
   int i;
   ThreadData thread[N];
   init_data(thread);

    for(i=0;i<N;i++){
        printf("jet[%d].condition=%d\n",thread[i].id,thread[i].condition);
        printf("-----------------------------------------\n");
    }

   pthread_mutex_init(&jet_mutex, NULL);

	   for(i=0; i<N; i++)
	   {
          	  thread[i].thread_num=i;
		  pthread_create(&(thread[i].thread_id), NULL, fly_API, (void *)(&thread[i]));
	   }

	   for (i = 0; i < N; i++){
		   pthread_join(thread[i].thread_id, NULL);
	   }

   pthread_mutex_destroy(&jet_mutex);
   return 0;
}

