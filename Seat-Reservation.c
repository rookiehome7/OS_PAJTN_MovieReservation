/* CPE326 - Operating Systems
 * Online Movie Reservation
 * Group: PAJTN
 * Phutthitham Kunapanyakorn  CPE 59070503439 phutthitham@gmail.com
 * Anchisa     Yodkaew        CPE 59070503465 kppooke@gmail.com
 * Jarit       Laoprasert     CPE 59070503466 franksam014@gmail.com
 * Takdanai    Jirawanichkul  CPE 59070503473 rookiehome7@gmail.com
 * Natcha      Klangplemchitt CPE 59070503487 natchaploy9@gmail.com  */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>
// gcc -Wall -Ipthread -o Online-Movie-Reservation Online-Movie-Reservation.c

#define MAXCHAR 64

#include <semaphore.h>

pthread_mutex_t lock;

sem_t seat_Sem1,seat_Sem2,seat_Sem3,seat_Sem4,seat_Sem5;
int seat1;
int seat2;
int seat3;
int seat4;
int seat5;

void initialize_Seat(){
 	seat1 = 0;
	seat2 = 0;
	seat3 = 0;
	seat4 = 0;
	seat5 = 0;
}

void delay(int milli_seconds) 
{ 
    // Stroing start time 
    clock_t start_time = clock(); 
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ; 
}

#define SEATWIDTH 6 //DEFAULT: 6 (FIXED)
#define SCREENWIDTH 70 //DEFAULT: 25
void printSeat()
{	
	printf("\n ^---------------------------^ \n");
	printf(" |           SCREEN          | \n");
	printf(" ^---------------------------^ \n");

	printf(" | %d | | %d | | %d | | %d | | %d |\n",seat1,seat2,seat3,seat4,seat5);
	printf(" O---O O---O O---O O---O O---O\n");
}

void programInstuction()
{
	printf("This is Program instuction\n");
	printf("In this program we have only 5 seat: number ( 1 2 3 4 5 )\n");
	printf("In simulation we will have 2 user (User A and User B)\n");
	printf("Each User need to input seat reservation consequently (Type -1 to finish)\n");
	printf("Please do not select same seat \n");
}



int prereservationSeat(int seatNumber,char name[5])
{
	delay(rand() % 1000);
	//printf(".");	
	if (seatNumber == 1){
		printf("\t%s:Seat%d > Wait for unlock\n",name,seatNumber);
		sem_wait(&seat_Sem1);
		printf("\t\t%s:Seat%d > Get Queue\n",name,seatNumber);
		return 1;
	}
	else if(seatNumber == 2){
		printf("\t%s:Seat%d > Wait for unlock\n",name,seatNumber);
		sem_wait(&seat_Sem2);
		printf("\t\t%s:Seat%d > Get Queue\n",name,seatNumber);
		return 1;
	}
	else if (seatNumber == 3){
		printf("\t%s:Seat%d > Wait for unlock\n",name,seatNumber);
		sem_wait(&seat_Sem3);
		printf("\t\t%s:Seat%d > Get Queue\n",name,seatNumber);
		return 1;
	}
	else if (seatNumber == 4 ){
		printf("\t%s:Seat%d > Wait for unlock\n",name,seatNumber);
		sem_wait(&seat_Sem4);
		printf("\t\t%s:Seat%d > Get Queue\n",name,seatNumber);
		return 1;
	}
	else if (seatNumber == 5){
		printf("\t%s:Seat%d > Wait for unlock\n",name,seatNumber);
		sem_wait(&seat_Sem5);
		printf("\t\t%s:Seat%d > Get Queue\n",name,seatNumber);
		return 1;
	}
	else{
		return 0;
	}
}

void reservationSeat(int seatNumber,char name[5])
{
	//printf(".");	
	if (seatNumber == 1){
		if ( seat1 == 0) // Reservation 
		{
			printf("%s:Reservation Seat %d\n",name,seatNumber);
			seat1 = 1;
		}
		else
		{
			printf("%s:Cannot Reservation Seat %d\n",name,seatNumber);
		}
		sem_post(&seat_Sem1);
	}
	else if(seatNumber == 2){
		if ( seat2 == 0) // Reservation 
		{
			printf("%s:Reservation Seat %d\n",name,seatNumber);
			seat2 = 1;
			
		}
		else
		{
			printf("%s:Cannot Reservation Seat %d\n",name,seatNumber);
		}
		sem_post(&seat_Sem2);
	}
	else if (seatNumber == 3){
		if ( seat3 == 0) // Reservation 
		{
			printf("%s:Reservation Seat %d\n",name,seatNumber);
			seat3 = 1;
		}
		else
		{
			printf("%s:Cannot Reservation Seat %d\n",name,seatNumber);
		}
		sem_post(&seat_Sem3);

	}
	else if (seatNumber == 4 ){
		if ( seat4 == 0) // Reservation 
		{
			printf("%s:Reservation Seat %d\n",name,seatNumber);
			seat4 = 1;
			
		}
		else
		{
			printf("%s:Cannot Reservation Seat %d\n",name,seatNumber);
		}
		sem_post(&seat_Sem4);
	}
	else if (seatNumber == 5){
		if ( seat5 == 0) // Reservation 
		{
			printf("%s:Reservation Seat %d\n",name,seatNumber);
			seat5 = 1;	
		}
		else
		{
			printf("%s:Cannot Reservation Seat %d\n",name,seatNumber);
		}
		sem_post(&seat_Sem5);
	}
	else{
		// error 
	}

}

//pthread_mutex_init(&lock, NULL);
// pthread_cond_init(&init, NULL);
// pthread_cond_init(&init2, NULL);


void *mythread(void *arg)
{
	int max = 0;
	int i = 0;
	int compare = 0;
	int temp = 0;

	int seatArray[5];
	char name[5];
	//printf("%s\n",(char*) arg);
	sscanf(arg,"%d:%d:%d:%d:%d:%d:%s",&max,&seatArray[0], &seatArray[1], &seatArray[2],&seatArray[3],&seatArray[4],name);
	for ( i = 0 ; i < max ; i++)
	{
	temp = prereservationSeat(seatArray[i],name); 
	compare = compare + temp;
	}
	//printf("Compare %d | %d\n",compare,max-1);
	for ( i = 0 ; i < max ; i++)
	{
	reservationSeat(seatArray[i],name); 
	}
	return NULL;
}



void simulation()
{
	char input[MAXCHAR];
	int choice = 0;
	int seat = 0;

	int userAChoice[5] ;
	int numberOfUserAChoice = 0;
	int userBChoice[5];
	int numberOfUserBChoice = 0;
	int index = 0;
	int i = 0;
	for ( i = 0 ; i < 5 ; i++)
	{
		userAChoice[i]=0;
		userBChoice[i]=0;
	}
	seat1=0;
	seat2=0;
	seat3=0;
	seat4=0;
	seat5=0;
	printf("Need Program instuction? (1:Yes|0:No): \n");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%d",&choice);
	if (choice == 1 )
		programInstuction();

	index = 0;
	printf("Input Seat for user A ( 1-5 Only Not Validate ) :\n");
	do{
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&seat);
		userAChoice[index] = seat;
		index = index + 1;
		if (index >= 5)
			break;
	}while(seat != -1);
	numberOfUserAChoice = index;

	index = 0;
	printf("Input seat for user B ( 1-5 Only Not Validate ) \n");
	do{
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&seat);
		userBChoice[index] = seat;
		index = index + 1;
		if (index >= 5)
			break;
	}while(seat != -1);
	numberOfUserBChoice = index;

	printf("User A select seat: ");
	for (i = 0 ; i < 5 ; i++){
		if (userAChoice[i] == -1 )
			break;	
		printf(" %d ",userAChoice[i]);
	}
	printf("\nUser B select seat: ");
	for (i = 0 ; i < 5 ; i++){
		if (userBChoice[i] == -1 )
			break;
		printf(" %d ",userBChoice[i]);
	}
	printf("\n");


	pthread_t p1,p2;
	int rc = pthread_mutex_init(&lock,NULL);
	assert(rc == 0);

	char inputA[25],inputB[25];

	sprintf(inputA, "%d:%d:%d:%d:%d:%d:A",numberOfUserAChoice,userAChoice[0],userAChoice[1],userAChoice[2],userAChoice[3],userAChoice[4]);
	sprintf(inputB, "%d:%d:%d:%d:%d:%d:B",numberOfUserBChoice,userBChoice[0],userBChoice[1],userBChoice[2],userBChoice[3],userBChoice[4]);
	pthread_create(&p1,NULL,mythread,inputA);
	pthread_create(&p2,NULL,mythread,inputB);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
}

int main(int argc, char *argv[])
{
	char input[64];
	int userChoice = 0;


	sem_init(&seat_Sem1,0,1);
	sem_init(&seat_Sem2,0,1);
	sem_init(&seat_Sem3,0,1);
	sem_init(&seat_Sem4,0,1);
	sem_init(&seat_Sem5,0,1);


	initialize_Seat();
	srand(time(NULL));   // Initialization, should only be called once.
	printf("---------------------------------------------------------------------------\n");
	printf(">>>>>>>>>>>>>>>>>>>  Online-Movie-Reservation System   <<<<<<<<<<<<<<<<<<<<\n");
	do {
		printf("---------------------------------------------------------------------------\n");
		printf("1:Simulation | 2:Print Seat | 0:Exit\nInput number : ");
		fgets(input,sizeof(input),stdin);
	 	sscanf(input,"%d",&userChoice);	
	 	if (userChoice == 1)
	 		simulation();
	 	else if (userChoice == 2)
	 		printSeat();
	 	else if (userChoice > 1)
	 		printf("Enter wrong choice Please enter it again.\n");
	 	else
	 		printf("End program Thankyou! Goodbye!\n");
	} while(userChoice > 0);
	// seat[0][1] = 1;
	// seat[2][1] = 1;
	// seat[4][3] = 1;
	return 0;
}

