/*********************************
 *  dec2bin                      *
 *                               *
 * Your basic run of the mill    *
 * base 10 to base 2 converter.  *
 *                               * 
 * Author: Doug Stanley          *
 *   Date: 2/3/14                *
 * Version: 1.0                  *
 *********************************/
#include <stdio.h>

int main(){
    unsigned int num, i = 0;
    unsigned char c = '\0';

    //We create a mask that has the top 1 bits set to start
    unsigned int MASK = 1<<31;

    printf("Enter number to convert: ");
    scanf("%u", &num);

    printf("\nBinary: ");
    
    for( i = 0; i < 32; i++ ){
        //print a space every 8 bits
        //to more easily see individual
        //bytes
        if( i > 0 && i % 8 == 0 ) printf(" ");

        //check if current bit is on or off
        if( (num & MASK) == MASK ) printf("1");
        else printf("0");

        //move the mask down one more bit
        MASK = MASK >> 1;
    }

    printf("\n");

    return 0;
}
