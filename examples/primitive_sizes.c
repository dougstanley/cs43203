/**********************************************
 * Sample code to print out the size in bytes
 * each of the C primitive types uses.
 *
 * Author: Doug Stanley <dmstanle@kent.edu>
 **********************************************/
#include <stdio.h>

//Notice, I had to include this file to have
//boolean support. It seems booleans are actually
//only supported more recently (well since like 99).
#include <stdbool.h>

int main() {

    printf("The size of a bool is: %d\n", (int)sizeof(bool));
    printf("The size of a char is: %d\n", (int)sizeof(char));
    printf("The size of a short is: %d\n", (int)sizeof(short));
    printf("The size of an int is: %d\n", (int)sizeof(int));
    printf("The size of a long int is: %d\n", (int)sizeof(long));
    printf("The size of a long long int is: %d\n", (int)sizeof(long long));
    printf("The size of a float is: %d\n", (int)sizeof(float));
    printf("The size of a double is: %d\n", (int)sizeof(double));
    printf("The size of a long double is: %d\n", (int)sizeof(long double));
    printf("The size of a pointer is: %d\n", (int)sizeof(void *));

    return 0;
}
