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

#define MAXSEAT_ROW 5
#define MAXSEAT_COLUMN 5

int seat[MAXSEAT_ROW][MAXSEAT_COLUMN];
void initialize_Seat()
{
	int row = 0;
	int column = 0;
	for(row = 0; row < MAXSEAT_ROW ; row++)
	{
		for(column = 0;column < 5;column++)
		{
			seat[row][column] = 0;
		}
	}
}
void printSeat()
{
	int row = 0;
	int column = 0;
	printf("+---+---+---+---+---+\n");
	for(row = 0; row < MAXSEAT_ROW ; row++)
	{
		for(column = 0;column < 5;column++)
		{
			printf("| %d ",seat[row][column]);
		}
		printf("|\n+---+---+---+---+---+\n");
	}
}

void generateFile()
{
	printf("\nGenerateFile function\n");
}
void runSimulation()
{
	printf("\nRun simulation function\n");
}
void testSimulation()
{
	printf("\nTest simulation function\n");
}

int main()
{
	char input[64];
	int userChoice = 0; 
	initialize_Seat();
	printf("Online-Movie-Reservation System\n");
	do {
		printf("\n\nSelect what you want to do\n");
		printf("1:Generate file\n2:Run simulation\n3:Test result\n4:Print Seat\n0:Exit Program\nInput number : ");
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

