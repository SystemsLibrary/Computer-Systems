/*
 * Unsigned Implications.c
 *
 *  Created on: 26 Apr 2021
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
	int cnt = 10;
	int a[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	unsigned i;

	for (i = cnt - 2; i < cnt; i--) // when i gets below zero, the i becomes the largest value
	{
		a[i] += a[i + 1];
	}

	return 0;
}
