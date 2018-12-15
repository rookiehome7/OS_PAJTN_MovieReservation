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



void prereservationSeat(int seatNumber,char name[5])
{
	delay(rand() % 1000);
	//printf(".");	
	if (seatNumber == 1){
		printf("\t%s:Seat%d > Wait for unlock\n",name,seatNumber);
		sem_wait(&seat_Sem1);
		printf("\t\t%s:Seat%d > Get Queue\n",name,seatNumber);

	}
	else if(seatNumber == 2){
		printf("\t%s:Seat%d > Wait for unlock\n",name,seatNumber);
		sem_wait(&seat_Sem2);
		printf("\t\t%s:Seat%d > Get Queue\n",name,seatNumber);

	}
	else if (seatNumber == 3){
		printf("\t%s:Seat%d > Wait for unlock\n",name,seatNumber);
		sem_wait(&seat_Sem3);
		printf("\t\t%s:Seat%d > Get Queue\n",name,seatNumber);

	}
	else if (seatNumber == 4 ){
		printf("\t%s:Seat%d > Wait for unlock\n",name,seatNumber);
		sem_wait(&seat_Sem4);
		printf("\t\t%s:Seat%d > Get Queue\n",name,seatNumber);

	}
	else if (seatNumber == 5){
		printf("\t%s:Seat%d > Wait for unlock\n",name,seatNumber);
		sem_wait(&seat_Sem5);
		printf("\t\t%s:Seat%d > Get Queue\n",name,seatNumber);

	}
	else{

	}
}

void reservationSeat(int seatNumber,char name[5])
{
	//printf(".");	
	delay(rand() % 1000);
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


void *mythread(void *arg)
{
	int max = 0;
	int i = 0;
	int seatArray[5];
	char name[5];
	//printf("%s\n",(char*) arg);
	sscanf(arg,"%d:%d:%d:%d:%d:%d:%s",&max,&seatArray[0], &seatArray[1], &seatArray[2],&seatArray[3],&seatArray[4],name);
	for ( i = 0 ; i < max ; i++)
	{
	prereservationSeat(seatArray[i],name); 
	}
	//printf("Compare %d | %d\n",compare,max-1);
	for ( i = 0 ; i < max ; i++)
	{
	reservationSeat(seatArray[i],name); 
	}
	return NULL;
}


// Deadlock problem not fix
void simulationDeadlock()
{
	char input[MAXCHAR];
	
	int seat = 0;
	int index = 0;

	int userAChoice[5],userBChoice[5];

	int numberOfUserAChoice = 0,numberOfUserBChoice = 0;


	int isSelect1,isSelect2,isSelect3,isSelect4,isSelect5;
	char inputA[25],inputB[25];

	// Reset value before running simulation function 
	for (index = 0 ; index < 5 ; index++) 
	{
		userAChoice[index]=0;
		userBChoice[index]=0;
	}
	seat1=0;
	seat2=0;
	seat3=0;
	seat4=0;
	seat5=0;

	/*
	int choice = 0;
	printf("Show Program instuction? (1:Yes | 0:No): \n");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%d",&choice);
	if (choice == 1 ) // Show program instuction 
		programInstuction();
	*/
	// Ask user A for input seat 
	index = 0;
	isSelect1 = 0;
	isSelect2 = 0;
 	isSelect3 = 0;
	isSelect4 = 0;
	isSelect5 = 0;
	printf("Input Seat for user A\n");
	do{
		printf("Seat number :");
		memset(input,0,sizeof(input));
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&seat);
		if ( ((seat < 1 ||  seat > 5) && seat != -1) || (seat == 1 && isSelect1 == 1) || (seat == 2 && isSelect2 == 1) || (seat == 3 && isSelect3 == 1) ||(seat == 4 && isSelect4 == 1) || (seat == 5 && isSelect5 == 1) )
		{

			printf("Invalid or Exist number try again -> ");
		}
		else
		{	
			userAChoice[index] = seat;
			index = index + 1;
			// For set exist seat not allow to select again 
			if (seat == 1)
				isSelect1 = 1;
			if (seat == 2)
				isSelect2 = 1;
			if (seat == 3)
				isSelect3 = 1;
			if (seat == 4)
				isSelect4 = 1;
			if (seat == 5)
				isSelect5 = 1;
			if (index >= 5)
				break;
		}	
	}while(seat != -1);
	numberOfUserAChoice = index;


	// Ask user B for input seat 
	index = 0;
	isSelect1 = 0;
	isSelect2 = 0;
 	isSelect3 = 0;
	isSelect4 = 0;
	isSelect5 = 0;
	printf("Input seat for user B\n");
	do{
		printf("Seat number :");
		memset(input,0,sizeof(input));
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&seat);
		if ( ((seat < 1 ||  seat > 5) && seat != -1)  || (seat == 1 && isSelect1 == 1) || (seat == 2 && isSelect2 == 1) || (seat == 3 && isSelect3 == 1) ||(seat == 4 && isSelect4 == 1) || (seat == 5 && isSelect5 == 1) )
		{
			printf("Invalid or Exist number try again -> ");
		}
		else
		{
			userBChoice[index] = seat;
			index = index + 1;
			// For set exist seat not allow to select again 
			if (seat == 1)
				isSelect1 = 1;
			if (seat == 2)
				isSelect2 = 1;
			if (seat == 3)
				isSelect3 = 1;
			if (seat == 4)
				isSelect4 = 1;
			if (seat == 5)
				isSelect5 = 1;
			if (index >= 5)
				break;
		}
	}while(seat != -1);
	numberOfUserBChoice = index;


	// Show UserA & UserB reservation overall 
	printf("User A select seat: ");
	for (index = 0 ; index < 5 ; index++){
		if (userAChoice[index] == -1 )
			break;	
		printf(" %d ",userAChoice[index]);
	}
	printf("\nUser B select seat: ");
	for (index = 0 ; index < 5 ; index++){
		if (userBChoice[index] == -1 )
			break;
		printf(" %d ",userBChoice[index]);
	}
	printf("\n");


	// Start Multi thread
	pthread_t p1,p2;
	int rc = pthread_mutex_init(&lock,NULL);
	assert(rc == 0);


	// Running 
	sprintf(inputA, "%d:%d:%d:%d:%d:%d:A",numberOfUserAChoice,userAChoice[0],userAChoice[1],userAChoice[2],userAChoice[3],userAChoice[4]);
	sprintf(inputB, "%d:%d:%d:%d:%d:%d:B",numberOfUserBChoice,userBChoice[0],userBChoice[1],userBChoice[2],userBChoice[3],userBChoice[4]);
	// B Priority Create thread b first 
	pthread_create(&p2,NULL,mythread,inputB);
	pthread_create(&p1,NULL,mythread,inputA);
	pthread_join(p2,NULL);
	pthread_join(p1,NULL);

	

	// Print seat 
	printSeat();
	
	// Running 
	// sprintf(inputA, "%d:%d:%d:%d:%d:%d:A",numberOfUserAChoice,userAChoice[0],userAChoice[1],userAChoice[2],userAChoice[3],userAChoice[4]);
	// sprintf(inputB, "%d:%d:%d:%d:%d:%d:B",numberOfUserBChoice,userBChoice[0],userBChoice[1],userBChoice[2],userBChoice[3],userBChoice[4]);
	// pthread_create(&p1,NULL,mythread,inputA);
	// pthread_create(&p2,NULL,mythread,inputB);
	// pthread_join(p1,NULL);
	// pthread_join(p2,NULL);
}


// Deadlock problem fix
void simulationNoDeadlock()
{
	char input[MAXCHAR];
	
	int seat = 0;
	int index = 0;

	int userAChoice[5],userBChoice[5];
	int userATime,userBTime; // Set time
	int numberOfUserAChoice = 0,numberOfUserBChoice = 0;


	int isSelect1,isSelect2,isSelect3,isSelect4,isSelect5;
	char inputA[25],inputB[25];

	// Reset value before running simulation function 
	for (index = 0 ; index < 5 ; index++) 
	{
		userAChoice[index]=0;
		userBChoice[index]=0;
	}
	seat1=0;
	seat2=0;
	seat3=0;
	seat4=0;
	seat5=0;

	/*
	int choice = 0;
	printf("Show Program instuction? (1:Yes | 0:No): \n");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%d",&choice);
	if (choice == 1 ) // Show program instuction 
		programInstuction();
	*/
	// Ask user A for input seat 
	index = 0;
	isSelect1 = 0;
	isSelect2 = 0;
 	isSelect3 = 0;
	isSelect4 = 0;
	isSelect5 = 0;
	printf("Input Seat for user A\n");
	do{
		printf("Seat number :");
		memset(input,0,sizeof(input));
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&seat);
		if ( ((seat < 1 ||  seat > 5) && seat != -1) || (seat == 1 && isSelect1 == 1) || (seat == 2 && isSelect2 == 1) || (seat == 3 && isSelect3 == 1) ||(seat == 4 && isSelect4 == 1) || (seat == 5 && isSelect5 == 1) )
		{

			printf("Invalid or Exist number try again -> ");
		}
		else
		{	
			userAChoice[index] = seat;
			index = index + 1;
			// For set exist seat not allow to select again 
			if (seat == 1)
				isSelect1 = 1;
			if (seat == 2)
				isSelect2 = 1;
			if (seat == 3)
				isSelect3 = 1;
			if (seat == 4)
				isSelect4 = 1;
			if (seat == 5)
				isSelect5 = 1;
			if (index >= 5)
				break;
		}	
	}while(seat != -1);
	numberOfUserAChoice = index;
	printf("User A Reservation time(Less come first)(more than 0):");
	do{
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%d",&userATime);
	}while(userATime < 1);
	

	// Ask user B for input seat 
	index = 0;
	isSelect1 = 0;
	isSelect2 = 0;
 	isSelect3 = 0;
	isSelect4 = 0;
	isSelect5 = 0;
	printf("Input seat for user B\n");
	do{
		printf("Seat number :");
		memset(input,0,sizeof(input));
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&seat);
		if ( ((seat < 1 ||  seat > 5) && seat != -1)  || (seat == 1 && isSelect1 == 1) || (seat == 2 && isSelect2 == 1) || (seat == 3 && isSelect3 == 1) ||(seat == 4 && isSelect4 == 1) || (seat == 5 && isSelect5 == 1) )
		{
			printf("Invalid or Exist number try again -> ");
		}
		else
		{
			userBChoice[index] = seat;
			index = index + 1;
			// For set exist seat not allow to select again 
			if (seat == 1)
				isSelect1 = 1;
			if (seat == 2)
				isSelect2 = 1;
			if (seat == 3)
				isSelect3 = 1;
			if (seat == 4)
				isSelect4 = 1;
			if (seat == 5)
				isSelect5 = 1;
			if (index >= 5)
				break;
		}
	}while(seat != -1);
	numberOfUserBChoice = index;
	printf("User B Reservation time(Less come first)(more than 0):");
	do{
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%d",&userBTime);
	}while(userBTime < 1);

	// Show UserA & UserB reservation overall 
	printf("User A (Booked time:%d) select seat: ",userATime);
	for (index = 0 ; index < 5 ; index++){
		if (userAChoice[index] == -1 )
			break;	
		printf(" %d ",userAChoice[index]);
	}
	printf("\nUser B (Booked time:%d) select seat: ",userBTime);
	for (index = 0 ; index < 5 ; index++){
		if (userBChoice[index] == -1 )
			break;
		printf(" %d ",userBChoice[index]);
	}
	printf("\n");


	// Start Multi thread
	pthread_t p1,p2;
	int rc = pthread_mutex_init(&lock,NULL);
	assert(rc == 0);

	// Insert Algorithm Avoid Deadlock here
	// Our group Algorithms create 
	//1.Check the time first which one come first ( If Equal A more priority )
	//2. Check seat inside have same or not 
	//3.1 If seat same we need to reject slower one ( to avoid deadlock )
	//3.2 Else Let's it run 
	// Gurantee No deadlock , 1 Reservation can get all seat . the reservation cannot get seat will error and get seat again
 	int j;
 	int isExist;
 	isExist = 0;
	if (userATime <= userBTime) // User A come first & equal
	{
		printf("A Priority\n");
		for (index = 0 ; index < 5 ; index++) // Loop A
		{
			if (userAChoice[index] == -1)
			{
				break;
			}
			for (j = 0 ; j < 5 ; j++)
			{
				if (userBChoice[j] == -1)
					{
					break;
					}
				else if (userBChoice[j] == userAChoice[index]  ) // Found same 
					{
					isExist = 1;
					break;
					}
			}
		}
		if (isExist == 1)
		{
		sprintf(inputA, "%d:%d:%d:%d:%d:%d:A",numberOfUserAChoice,userAChoice[0],userAChoice[1],userAChoice[2],userAChoice[3],userAChoice[4]);
		pthread_create(&p1,NULL,mythread,inputA);
		pthread_join(p1,NULL);
		printf("\nFOUND SAME REJECT B ---- B Cannot reservation need to select seat again\n");
		}
		else
		{
		// Running 
		sprintf(inputA, "%d:%d:%d:%d:%d:%d:A",numberOfUserAChoice,userAChoice[0],userAChoice[1],userAChoice[2],userAChoice[3],userAChoice[4]);
		sprintf(inputB, "%d:%d:%d:%d:%d:%d:B",numberOfUserBChoice,userBChoice[0],userBChoice[1],userBChoice[2],userBChoice[3],userBChoice[4]);
		// A Priority Create thread A first 
		pthread_create(&p1,NULL,mythread,inputA);
		pthread_create(&p2,NULL,mythread,inputB);
		pthread_join(p1,NULL);
		pthread_join(p2,NULL);
		}
	
	}
	else  // User B come first l
	{
		printf("B Priority\n");
		for (index = 0 ; index < 5 ; index++) // Loop A
		{
			if (userBChoice[index] == -1)
			{
				break;
			}
			for (j = 0 ; j < 5 ; j++)
			{
				if (userAChoice[j] == -1)
					{
					break;
					}
				else if (userAChoice[j] == userBChoice[index]  ) // Found same 
					{
					isExist = 1;
					break;
					}
			}
		}
		if (isExist == 1)
		{
		
		sprintf(inputB, "%d:%d:%d:%d:%d:%d:B",numberOfUserBChoice,userBChoice[0],userBChoice[1],userBChoice[2],userBChoice[3],userBChoice[4]);
		pthread_create(&p2,NULL,mythread,inputB);
		pthread_join(p2,NULL);
		printf("\nFOUND SAME REJECT A ---- A Cannot reservation need to select seat again\n");
		}
		else
		{
		// Running 
		sprintf(inputA, "%d:%d:%d:%d:%d:%d:A",numberOfUserAChoice,userAChoice[0],userAChoice[1],userAChoice[2],userAChoice[3],userAChoice[4]);
		sprintf(inputB, "%d:%d:%d:%d:%d:%d:B",numberOfUserBChoice,userBChoice[0],userBChoice[1],userBChoice[2],userBChoice[3],userBChoice[4]);
		// B Priority Create thread b first 
		pthread_create(&p2,NULL,mythread,inputB);
		pthread_create(&p1,NULL,mythread,inputA);
		pthread_join(p2,NULL);
		pthread_join(p1,NULL);
		
		}
	
	}
	// Print seat 
	printSeat();
	
	// Running 
	// sprintf(inputA, "%d:%d:%d:%d:%d:%d:A",numberOfUserAChoice,userAChoice[0],userAChoice[1],userAChoice[2],userAChoice[3],userAChoice[4]);
	// sprintf(inputB, "%d:%d:%d:%d:%d:%d:B",numberOfUserBChoice,userBChoice[0],userBChoice[1],userBChoice[2],userBChoice[3],userBChoice[4]);
	// pthread_create(&p1,NULL,mythread,inputA);
	// pthread_create(&p2,NULL,mythread,inputB);
	// pthread_join(p1,NULL);
	// pthread_join(p2,NULL);
}

int main(int argc, char *argv[])
{
	char input[MAXCHAR];
	int userChoice = 0;
	srand(time(NULL));   // Initialization, should only be called once.

	//Intial Semephore Value
	sem_init(&seat_Sem1,0,1);
	sem_init(&seat_Sem2,0,1);
	sem_init(&seat_Sem3,0,1);
	sem_init(&seat_Sem4,0,1);
	sem_init(&seat_Sem5,0,1);

	// Reset all seat to 0
	initialize_Seat();

	printf("---------------------------------------------------------------------------\n");
	printf(">>>>>>>>>>>>>>>>>>>  Online-Movie-Reservation System   <<<<<<<<<<<<<<<<<<<<\n");
	do {
		printf("---------------------------------------------------------------------------\n");
		printf("1:Simulation(DeadLock) | 2:Simulation(No Deadlock) | 0:Exit\nInput number : ");
		memset(input,-1,sizeof(input));
		userChoice = -1;
		fgets(input,sizeof(input),stdin);
	 	sscanf(input,"%d",&userChoice);	
	 	if (userChoice == 1)
	 	{
	 		printf("Deadlock situation + individual reservation seat\n");
	 		simulationDeadlock();
	 	}
	 	else if (userChoice == 2){
	 		printf("Deadlock Prevention no Deadlock\n");
	 		simulationNoDeadlock();
	 	}
	 	else if (userChoice > 2 || userChoice < 0)
	 		printf("Enter wrong choice Please enter it again.\n");
	 	else
	 		printf("End program Thankyou! Goodbye!\n");
	} while(userChoice != 0);
	return 0;
}

