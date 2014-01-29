/*********************************
 *  dec2hex                      *
 *                               *
 * Your basic run of the mill    *
 * base 10 to base 16 converter. *
 *                               * 
 * Author: Doug Stanley          *
 *   Date: 1/29/14               *
 * Version: 1.0                  *
 *********************************/
#include <stdio.h>

int main(){
    unsigned int num, i, tmp = 0;
    unsigned char c = '\0';

    //We create a mask that has the top 4 bits on
    const unsigned int MASK = (15 << 28);

    printf("Enter number to convert: ");
    scanf("%u", &num);

    printf("\nHex: 0x");

    for( i = 0, tmp = num; i < 8; i++ ){
        c = (tmp & MASK) >> 28;
        if( c < 10 ) c += 48;
        else c += 55;
        printf("%c", c);
        tmp = tmp << 4;
    }

    printf("\n");

    return 0;
}
