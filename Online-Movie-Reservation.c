/*
 * CPE326 - Operating Systems
 * Online Movie Reservation
 * Group: PAJTN
 * Phutthitham Kunapanyakorn  CPE 59070503439 phutthitham@gmail.com
 * Anchisa     Yodkaew        CPE 59070503465 kppooke@gmail.com
 * Jarit       Laoprasert     CPE 59070503466 franksam014@gmail.com
 * Takdanai    Jirawanichkul  CPE 59070503473 rookiehome7@gmail.com
 * Natcha      Klangplemchitt CPE 59070503487 natchaploy9@gmail.com
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define MAXSEAT_ROW 10
#define MAXSEAT_COLUMN 10

#define MAXCHAR 64

int seat[MAXSEAT_ROW][MAXSEAT_COLUMN];

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

// void printSeat()
// {
// 	int row = 0;
// 	int column = 0;
// 	printf("+---+---+---+---+---+---+---+---+---+---+\n");
// 	printf("+-------------- S C R E E N ------------+");
// 	for(row = 0; row < MAXSEAT_ROW ; row++)
// 	{
// 		printf("\n+---+---+---+---+---+---+---+---+---+---+\n|");
// 		for(column = 0;column < MAXSEAT_COLUMN;column++)
// 		{
// 			if ( seat[row][column] == 1 )
// 			{
// 				printf(" X |",seat[row][column]);
// 			}
// 			else 
// 			{
// 				printf("   |",seat[row][column]);
// 			}
			
// 		}
		
// 	}
// 	printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
// }

#define SEATWIDTH 6 //DEFAULT: 6 (FIXED)
#define SCREENWIDTH 70 //DEFAULT: 25

void printSeat()
{	
	int i=0;
	int j=0;
	
	printf("\n");
	
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
			if ( seat[i][j] == 1 )
			{
				printf(" | X | ",seat[i][j]);
			}
			else 
			{
				printf(" |   | ");
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


// Sorting reservation array 
// To sorting reservation time 
// Return : no return
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
		printf("ID:%d\t Seat [%d],[%d] \t Time:%d\n",reservation[i].userID,
															reservation[i].row,
															reservation[i].column,
															reservation[i].time);
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



// Return function
// 1 : Save success 0 : Seat exist 
int reservationSeat(int row, int column)
{
	if (seat[row][column] == 0) // NO RESERVATION YET
	{
	seat[row][column] = 1;		
	return 1;
	}
	else // Have reservation
	{
	return 0;
	}
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
		reservation[i].userID = rand() % 100;
		reservation[i].time = rand() % 100;
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

// Run Simulation 
void runSimulation()
{
	printf("---------------------------------------------------------------------------\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>   RUN SIMULATION TEST   <<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("---------------------------------------------------------------------------\n");
	char input[MAXCHAR];
	char fileName[MAXCHAR];

	int userID = 0;
	int column = 0;
	int row = 0;
	int time = 0;

	int i = 0;
	int maxReservation = 0 ;
	initialize_Seat(); // Reset Seat 

	int isSuccess = 0;
	int countComplete = 0;
	int countInComplete = 0;

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
		printf("Total Incoming event:%d\n",maxReservation);
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
		for ( i = 0 ; i < maxReservation ; i++ )
		{
			isSuccess = reservationSeat(reservation[i].row,reservation[i].column);
			if (isSuccess == 1) // Reservation Complete 
			{
				reservation[i].isComplete = 1;
				countComplete = countComplete + 1;
			}
			else
			{
				reservation[i].isComplete = 0;
				countInComplete = countInComplete + 1;
			}
		}
		printSeat();
		printf("Reservation complete:%d\n",countComplete);
		for ( i = 0 ; i < maxReservation ; i++ )
		{
			if (reservation[i].isComplete == 1)
			{
				printf("%d ",reservation[i].userID);
			}
		}
		printf("\n");
		printf("Cannot Reservation:%d\n",countInComplete);
		for ( i = 0 ; i < maxReservation ; i++ )
		{
			if (reservation[i].isComplete == 0)
			{
				printf("%d ",reservation[i].userID);
			}
		}
		printf("\n");
	}
	fclose(pReadFile);
}

void testSimulation()
{
	printf("---------------------------------------------------------------------------\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>   TEST SIMULATION   <<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("---------------------------------------------------------------------------\n");
}

int main()
{
	char input[64];
	int userChoice = 0; 
	initialize_Seat();
	srand(time(NULL));   // Initialization, should only be called once.
	printf("---------------------------------------------------------------------------\n");
	printf(">>>>>>>>>>>>>>>>>>>  Online-Movie-Reservation System   <<<<<<<<<<<<<<<<<<<<");
	do {
		printf("\n---------------------------------------------------------------------------\n");
		printf("Select what you want to do\n");
		printf("1:Generate file | 2:Run simulation | 3:Test result | 4:Print Seat | 0:Exit\nInput number : ");
		fgets(input,sizeof(input),stdin);
	 	sscanf(input,"%d",&userChoice);	
	 	if (userChoice == 1)
	 		generateFile();
	 	else if (userChoice == 2)
	 		runSimulation();
	 	else if (userChoice == 3)
	 		testSimulation();
	 	else if (userChoice == 4)
	 		printSeat();
	 	else if (userChoice > 4)
	 		printf("Enter wrong choice Please enter it again.\n");
	 	else
	 		printf("End program Thankyou! Goodbye!\n");
	} while(userChoice > 0);
	// seat[0][1] = 1;
	// seat[2][1] = 1;
	// seat[4][3] = 1;
	return 0;
}

