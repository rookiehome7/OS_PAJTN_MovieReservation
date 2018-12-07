/*
 * CPE326 - Operating Systems
 *
 * Online Movie Reservation
 *
 * Group: PAJTN
 *
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

int seat[5][5];

void initialize()
{
	int i=0;
	int j=0;
	
	printf("+---+---+---+---+---+\n");
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			seat[i][j]=0;
			printf("| %d ",seat[i][j]);
		}
		
		printf("|\n+---+---+---+---+---+\n");
	}
}

int main()
{
	initialize();
	return 0;
}