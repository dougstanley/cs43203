/***********************************************
 * date.c
 *
 * Simple program to demonstrate the
 * use of scanf to parse an input string.
 *
 *  Author: Doug Stanley <dmstanle@kent.edu>
 *    Date: 1/29/14
 * Version: 1.0
 ***********************************************/

#include <stdio.h> //stdio.h is what has printf and scanf

int main(){
	unsigned int m,d,y;
	
	printf("Please enter a date (MM/DD/YY): ");

    //Take a date string in the form MM/DD/YY
    //and put just the numbers into 3 separate
    //variables
	scanf("%d/%d/%d",&m,&d,&y);

    //print the date back out using the numbers
    //we scanf'd in from the user:
	printf("\nYou entered: %02d/%02d/%02d\n", m, d, y);

	return 0;
}

