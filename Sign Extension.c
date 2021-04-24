/*
 * sign extension.c
 *
 *  Created on: 24 Apr 2021
 *      Author: Grant
 */

#include <stdio.h>

int decToBinary(int n)
{
    for (int i = 31; i >= 0; i--) {
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
	short int x = 15213;
	int ix = (int) x;
	short int y = -15213;
	int iy = (int) y;

	decToBinary(ix);
	decToBinary(iy);

	return 0;
}
