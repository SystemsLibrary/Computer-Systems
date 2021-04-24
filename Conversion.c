/*
 * Conversion.c
 *
 *  Created on: 24 Apr 2021
 *      Author: Grant
 */

#include <stdio.h>

int decToBinary(int n)
{
    for (int i = 15; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}


int main()
{
	int tx;
	int ty = -1;
	unsigned int ux = 4294967295;
	unsigned int uy;

	tx = ux;

	uy = ty;

	printf("tx is %d\n", tx);
	printf("uy is %u\n", uy);

	return 0;
}
