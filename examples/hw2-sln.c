/***********************************************
 * homework #2 solution
 *
 *  Author: Doug Stanley <dmstanle@kent.edu>
 *    Date: 2/10/14
 * Version: 1.0
 ***********************************************/

#include <stdio.h> //stdio.h is what has printf and scanf

int main(){
	unsigned int n1,n2,n3,n4 = 0;
    unsigned int IPA, IPB, MASK = 0;
	
	printf("Enter first IP (xxx.xxx.xxx.xxx): ");
	scanf("%u.%u.%u.%u", &n1, &n2, &n3, &n4);
    IPA = n1<<24 | n2<<16 | n3<<8 | n4;

	printf("Enter Subnet Mask (xxx.xxx.xxx.xxx): ");
	scanf("%u.%u.%u.%u", &n1, &n2, &n3, &n4);
    MASK = n1<<24 | n2<<16 | n3<<8 | n4;

	printf("Enter second IP (xxx.xxx.xxx.xxx): ");
	scanf("%u.%u.%u.%u", &n1, &n2, &n3, &n4);
    IPB = n1<<24 | n2<<16 | n3<<8 | n4;

    if( (IPA & MASK) == (IPB & MASK) ) printf("Both addresses in the same subnet!\n");
    else printf("Those IP Addresses are NOT on the same subnet!\n");

	return 0;
}
