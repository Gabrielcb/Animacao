#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 10 
#define max_ticket 20
#define black 1
#define white 2

volatile int choosing[N] = {0,0,0,0,0,0,0,0,0,0};
volatile int num[N] = {0,0,0,0,0,0,0,0,0,0};
volatile int color = 1;
volatile int my_color[N] = {0,0,0,0,0,0,0,0,0,0};

int max(int index);
int max_my_color(int index);
void change_color(int index);
int my_ticket_is_greater(int index_0, int index_1);
void attendance(int index);


void *customer(void *v){

	int index  = *(int*)v;
	int j;

    choosing[index] = 1;
	my_color[index] = black;
    num[index] = max(index) + 1;
    choosing[index] = 0;

    for(j = 0; j < N; j++){
    	while(choosing[j]);
    	while(my_ticket_is_greater(index, j));
    }
    
    
    printf("Customer %d is being attended\n", num[index]);
    attendance(index);

    if(my_color[index] == max_ticket)
    	change_color(index);

    num[index] = 0;
    
    return NULL;
}

int max(int index){
	int i;
	int maximum = 0;
	for(i = 0; i < N; i++){
		if(my_color[index] == my_color[i]){
             if(num[i] > maximum)
             	maximum = num[i];		
        }
	}
	return maximum;
}

int my_ticket_is_greater(int index_0, int index_1){
	if(my_color[index_0] != my_color[index_1]){
        if(my_color[index_0] == color)
          	return 1;
        return 0;
	} else {
        if(num[index_0] > num[index_1])
        	return 1;
        else if(num[index_0] == num[index_1]){
        	if(index_0 > index_1)
        		return 1;
        	else
        		return 0;
        } else {
        	return 0;
        }

	}
}



void change_color(int index){
	if(my_color[index] == black)
		my_color[index] = white;
	else
		my_color[index] = black;
}

void attendance(int index){

	printf("_ _ _ _\n");
	printf("password: %d\n", index);
	printf(" :-)  |__  (-:0 \n");
	sleep(1);
	printf("I would like a bread\n");
	sleep(1);
	printf("here is sir\n");
	sleep(1);
	printf("Thank you\n");
	printf("(-: |_ (-:0\n");
    sleep(1);		
	printf("You are welcome, bye!\n");	
	printf("_ _ _ _\n");
	sleep(1);

}

int main(){

	pthread_t thr[N]; 
	int id[N];
    int i;

	for(i = 0; i < N; i++){
		id[i] = i;
		pthread_create(&thr[i], NULL, customer, &id[i]);
	}	

    for(i = 0; i < N; i++)
		pthread_join(thr[i], NULL);

	return 0;
}