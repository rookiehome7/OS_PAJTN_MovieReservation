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
#define MAXSEAT_ROW 10
#define MAXSEAT_COLUMN 10
#define MAXCHAR 64
#define SEATWIDTH 6 //DEFAULT: 6 (FIXED)
#define SCREENWIDTH 70 //DEFAULT: 25
int seat[MAXSEAT_ROW][MAXSEAT_COLUMN];
int seatCapacity;
int countComplete;
int countInComplete;
int sumID;
pthread_mutex_t lock;

void initialize_Seat()
{
	int row = 0;
	int column = 0;
	for(row = 0; row < MAXSEAT_ROW ; row++)
	{
		for(column = 0;column < MAXSEAT_COLUMN;column++)
		{
			seat[row][column] = 0;
		}
	}
}
void delay(int milli_seconds) 
{ 
    // Stroing start time 
    clock_t start_time = clock(); 
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ; 
}
void printSeat()
{	
	int i=0;
	int j=0;
	
	//Center the movie screen.
	for(i=0;i<MAXSEAT_ROW*SEATWIDTH/2-SCREENWIDTH/2;i++)printf(" ");printf("^");for(i=0;i<SCREENWIDTH-2;i++)printf(" ");printf("^\n");
	for(i=0;i<MAXSEAT_ROW*SEATWIDTH/2-SCREENWIDTH/2;i++)printf(" ");printf("+");for(i=0;i<SCREENWIDTH-2;i++)printf("-");printf("+\n");
	for(i=0;i<MAXSEAT_ROW*SEATWIDTH/2-SCREENWIDTH/2;i++)printf(" ");printf("|");for(i=0;i<SCREENWIDTH-2;i++)printf(" ");printf("|\n");
	for(i=0;i<MAXSEAT_ROW*SEATWIDTH/2-SCREENWIDTH/2;i++)printf(" ");printf("|");for(i=0;i<SCREENWIDTH-2;i++)printf(" ");printf("|\n");
	for(i=0;i<MAXSEAT_ROW*SEATWIDTH/2-SCREENWIDTH/2;i++)printf(" ");printf("O");for(i=0;i<SCREENWIDTH-2;i++)printf("_");printf("O\n");
	for(i=0;i<MAXSEAT_ROW*SEATWIDTH/2-SCREENWIDTH/2;i++)printf(" ");printf("T");for(i=0;i<SCREENWIDTH-2;i++)printf(" ");printf("T\n");
	
	printf("\n");
	for(i=0;i<MAXSEAT_ROW;i++)
	{
		for(j=0;j<MAXSEAT_ROW;j++)
		{
			if ( seat[i][j] == 0 ) // NOT have reservation
			{
				printf(" |   | ");
			}
			else 
			{
				printf(" | %2d| ",seat[i][j]);
			}
		}
		
		printf("\n");
		
		for(j=0;j<MAXSEAT_ROW;j++)
		{
			printf(" O---O ");
		}
		printf("\n\n");
	}
}
typedef struct
{
     int userID;
     int column;
     int row;
     int time;
     int isComplete;
} RESERVATION_T;

void sortArray(RESERVATION_T reservation[],int maxData)
{
	RESERVATION_T temp;
	 /*   Bubble sorting begins */
    for (int i = 0; i < maxData; i++)
    {
        for (int j = 0; j < (maxData - i - 1); j++)
        {
            if (reservation[j].time > reservation[j+1].time)
            {
                temp = reservation[j];
                reservation[j]  = reservation[j+1] ;
                reservation[j+1]  = temp;
            }
        }
    }
}

void printFile(RESERVATION_T reservation[],int maxData)
{
	for (int  i = 0 ; i < maxData ; i++)
	{
		printf("ID:%d\t Seat [%d],[%d] \t Time:%d\n",reservation[i].userID,reservation[i].row,reservation[i].column,reservation[i].time);
	}	
}
void saveReservationFile(RESERVATION_T reservation[],int maxData)
{
	char input[MAXCHAR];
	char fileName[MAXCHAR];
	FILE *pWriteFile = NULL;
	printf("Enter filename:");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%s",fileName);
	pWriteFile = fopen(fileName,"w");
	if (pWriteFile == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(pWriteFile,"%d\n",maxData); // save number of data on top
	for (int  i = 0 ; i < maxData ; i++){
		fprintf(pWriteFile,"%d:%d:%d:%d\n",reservation[i].userID,reservation[i].row,reservation[i].column,reservation[i].time);
	}	
	printf("Save file %s finish\n",fileName);
	fclose(pWriteFile);
}
// Generate FILE 
void generateFile()
{
	char input[MAXCHAR];
	int isSave = 0;
	int maxData = 0; 
	printf("How many reservation you want to create: ");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%d",&maxData);

	RESERVATION_T reservation[maxData];

	printf("\nGenerate Reservation seat File \n");
	for ( int i = 0 ; i < maxData ; i++){
		reservation[i].userID = ((rand() % 100) + 1);
		reservation[i].time = rand() % 300;
		reservation[i].column = rand() % 10; 
		reservation[i].row = rand() % 10; 
	}
	// printf("Before sorting\n");
	// printFile(reservation,maxData);
	sortArray(reservation,maxData);

	printf("After sorting\n");
	printFile(reservation,maxData);
	printf("Want to save file? (1:yes:other:no) : ");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%d",&isSave);
	if ( isSave == 1 )
		{
		saveReservationFile(reservation,maxData);
		}
}
void reservationSeat(int id,int row, int column)
{
	//printf(".");	
	delay(rand() % 50);  // RANDOM DELAY 0-100 MS 
	if (seat[row][column] == 0) // NO RESERVATION YET
	{
	seat[row][column] = id;
	sumID = sumID + id;
	countComplete = countComplete + 1;
	seatCapacity = seatCapacity - 1; 	
	}
	else // Have reservation
	{
	countInComplete = countInComplete + 1;
	}
}
void *mythread(void *arg)
{
	int id,column,row;
	char text[16];
	sscanf(arg,"%d:%d:%d:%s",&id, &row, &column,text);
	reservationSeat(id,row,column);
	printf("%s ", text);
	return NULL;
}
void reservationSeatLock(int id,int row, int column)
{
	//printf(".");	
	delay(rand() % 50);  // RANDOM DELAY 0-100 MS 

	if (seat[row][column] == 0) // NO RESERVATION YET
	{

	pthread_mutex_lock(&lock);
	seat[row][column] = id;
	sumID = sumID + id;
	countComplete = countComplete + 1;
	seatCapacity = seatCapacity - 1; 	
	pthread_mutex_unlock(&lock);
	}
	else // Have reservation
	{
	pthread_mutex_lock(&lock);	
	countInComplete = countInComplete + 1;
	pthread_mutex_unlock(&lock);
	}

}
void *mythreadlock(void *arg)
{
	int id,column,row;
	char text[16];
	sscanf(arg,"%d:%d:%d:%s",&id, &row, &column,text);
	reservationSeatLock(id,row,column);
	printf("%s ", text);
	return NULL;
}
void runSimulation()
{
	printf("---------------------------------------------------------------------------\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>   RUN SIMULATION TEST   <<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("---------------------------------------------------------------------------\n");
	char input[MAXCHAR];
	char fileName[MAXCHAR];
	clock_t start, end;
	double cpu_time_used;
	int userID = 0;
	int column = 0;
	int row = 0;
	int time = 0;

	int i = 0;
	int maxReservation = 0 ;


	initialize_Seat(); // Reset Seat 

	countComplete = 0;
	countInComplete = 0;

	FILE *pReadFile = NULL;
	printf("Enter filename: ");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%s",fileName);
	pReadFile = fopen(fileName,"r");
	if (pReadFile == NULL)
	{
	    printf("Error reading %s file!\n",fileName);
	    exit(1);
	}
	else
	{
		// READ FILE PART 
		fgets(input,sizeof(input),pReadFile);
		sscanf(input,"%d",&maxReservation);
		printf("Number of Request:%d\n",maxReservation);
		seatCapacity = 100;
		RESERVATION_T reservation[maxReservation];
		while (fgets(input,sizeof(input),pReadFile) !=  NULL )
		{
			sscanf(input,"%d:%d:%d:%d", &userID, &column, &row, &time);
			reservation[i].userID = userID;
			reservation[i].time = time;
			reservation[i].column = column; 
			reservation[i].row = row;
			//printf("%d, %d, %d, %d\n",reservation[i].userID,reservation[i].column,reservation[i].row,reservation[i].time);
			i = i + 1;
		}
		// SIMULATION START
		start = clock();  // Start timer 
		sumID = 0;
		printf("Loading . . ."); 
		for ( i = 0 ; i < maxReservation ; i++ )
		{
			reservationSeat(reservation[i].userID,reservation[i].row,reservation[i].column);
		}
	    end = clock(); // Stop timer  
	    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	 
		//printSeat();
		
		// for (i=0;i<MAXSEAT_ROW;i++)
		// {
		// 	for (int j=0;j<MAXSEAT_COLUMN;j++)
		// 	{
		// 		if (seat[i][j] != 0)
		// 		{
		// 			//sumID = sumID + seat[i][j];
		// 			//printf("%d ",seat[i][j]);
		// 		}
		// 	}
		// }
		printf("\n--------------------------- Reservation Result ----------------------------\n");
		printf("Reservation Accept:%3d. Reservation Reject:%3d\n",countComplete,countInComplete);
		printf("Time usage: %.5lf Second\n",cpu_time_used);
		printf("Seat avaiable (%d/100) : Sum_ID %d\n",seatCapacity,sumID);
		printf("Error %d\n",(maxReservation - countComplete - countInComplete));
	}
	fclose(pReadFile);
}
// Send argument lock = 1 / no lock = 0 
void runMultiThreadSimulationNew(int lockSignal)
{
	printf("---------------------------------------------------------------------------\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>   RunMultiThreadSimulation   <<<<<<<<<<<<<<<<<<<<<<\n");
	if (lockSignal)
		printf("-------------------------------   WITH LOCK   -----------------------------\n");	
	printf("---------------------------------------------------------------------------\n");
	
	// Local Variable Decare 
	char input[MAXCHAR];
	char fileName[MAXCHAR];
	clock_t start, end;
	double cpu_time_used;
	int userID = 0;
	int column = 0;
	int row = 0;
	int time = 0;
	int i = 0;
	RESERVATION_T *reservation;

	// Multi-thread  
	pthread_t p1,p2,p3,p4;
	int maxReservation = 0 ;
	int rc = pthread_mutex_init(&lock,NULL);
	assert(rc == 0);

	// Global Variable Decare & Reset
	sumID = 0; 
	countComplete = 0;
	countInComplete = 0;
	seatCapacity = 100;
	
	initialize_Seat(); // Reset Seat 

	// Read Write file  
	FILE *pReadFile = NULL;
	printf("Enter filename: ");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%s",fileName);
	pReadFile = fopen(fileName,"r");
	if (pReadFile == NULL)
	{
	    printf("Error reading %s file!\n",fileName);
	    exit(1);
	}
	else
	{
		// Get reqeust from file 
		fgets(input,sizeof(input),pReadFile);
		sscanf(input,"%d",&maxReservation);
		printf("Number of Request:%d\n",maxReservation);

		// Memory Allocation   
		reservation = (RESERVATION_T*)calloc(maxReservation, sizeof(RESERVATION_T));

		// Phase string from text file to variable : Reservation 
		while (fgets(input,sizeof(input),pReadFile) !=  NULL )
		{
			sscanf(input,"%d:%d:%d:%d", &userID, &column, &row, &time);
			reservation[i].userID = userID;
			reservation[i].time = time;
			reservation[i].column = column; 
			reservation[i].row = row;
			i = i + 1;
		}
		// SIMULATION START
		start = clock();  // Start timer 
		for ( i = 0 ; i < maxReservation ; i = i + 4 )
		{
			printf(">");
			char inputThread[25],inputThread2[25],inputThread3[25],inputThread4[25];
			sprintf(inputThread, "%d:%d:%d:1",reservation[i].userID, reservation[i].row, reservation[i].column);
			if (i < maxReservation-1)
				sprintf(inputThread2, "%d:%d:%d:2",reservation[i+1].userID, reservation[i+1].row, reservation[i+1].column);
			if (i < maxReservation-2)
				sprintf(inputThread3, "%d:%d:%d:3",reservation[i+2].userID, reservation[i+2].row, reservation[i+2].column);
			if (i < maxReservation-3)
				sprintf(inputThread4, "%d:%d:%d:4",reservation[i+3].userID, reservation[i+3].row, reservation[i+3].column);	

			// Create Work to thread function 
			if (lockSignal){
				pthread_create(&p1,NULL,mythreadlock,inputThread);
				if (i < maxReservation-1)
					pthread_create(&p2,NULL,mythreadlock,inputThread2);
				if (i < maxReservation-2)
					pthread_create(&p3,NULL,mythreadlock,inputThread3);
				if (i < maxReservation-3)
					pthread_create(&p4,NULL,mythreadlock,inputThread4);	
			}
			else {
				pthread_create(&p1,NULL,mythread,inputThread);
				if (i < maxReservation-1)
					pthread_create(&p2,NULL,mythread,inputThread2);
				if (i < maxReservation-2)
					pthread_create(&p3,NULL,mythread,inputThread3);
				if (i < maxReservation-3)
					pthread_create(&p4,NULL,mythread,inputThread4);	
			}
			pthread_join(p1,NULL);
			if (i < maxReservation-1)
				pthread_join(p2,NULL);
			if (i < maxReservation-2)
				pthread_join(p3,NULL);
			if (i < maxReservation-3)
				pthread_join(p4,NULL);
			printf("\t");
		}
	    end = clock(); // Stop timer  
	    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	    
	    printf("\n--------------------------- Reservation Result ----------------------------\n");
		printf("Reservation Accept:%3d. Reservation Reject:%3d\n",countComplete,countInComplete);
		printf("Time usage: %.5lf Second\n",cpu_time_used);
		printf("Seat avaiable (%d/100) : Sum_ID %d\n",seatCapacity,sumID);
		printf("Error %d\n",(maxReservation - countComplete - countInComplete));
	}
	fclose(pReadFile);
	free(reservation);
}

int main(int argc, char *argv[])
{
	char input[64];
	int userChoice = 0;
	int lock = 0; 
	initialize_Seat();
	srand(time(NULL));   // Initialization, should only be called once.
	printf("---------------------------------------------------------------------------\n");
	printf(">>>>>>>>>>>>>>>>>>>  Online-Movie-Reservation System   <<<<<<<<<<<<<<<<<<<<\n");
	do {
		printf("---------------------------------------------------------------------------\n");
		printf("1:Run Thread\n2:Run Multi Thread\n3:Run Multi Thread LOCK\n4:Create file\n5:Print\n0:Exit\nInput number : ");
		fgets(input,sizeof(input),stdin);
	 	sscanf(input,"%d",&userChoice);	
	 	if (userChoice == 1)
	 		runSimulation();
	 	else if (userChoice == 2)
	 	{
	 		lock = 0;
	 		runMultiThreadSimulationNew(lock);
	 	}
	 	else if (userChoice == 3)
	 	{
	 		lock = 1;
	 		runMultiThreadSimulationNew(lock);
	 	}
	 	else if (userChoice == 4)
	 		generateFile();
	 	else if (userChoice == 5)
	 		printSeat();
	 	else if (userChoice > 5)
	 		printf("Enter wrong choice Please enter it again.\n");
	 	else
	 		printf("End program Thankyou! Goodbye!\n");
	} while(userChoice > 0);
	// seat[0][1] = 1;
	// seat[2][1] = 1;
	// seat[4][3] = 1;
	return 0;
}

