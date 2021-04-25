/*
 * operands.c
 *
 *  Created on: 25 Apr 2021
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
	int w = 60000;
	int ww = 60000;
	int w1 = w + ww;
	unsigned short w2 = (unsigned short) (w + ww);

	int y = 60000;
	int y1 = y * 5;
	unsigned short y2 = (unsigned short) (y * 5);

	int u = 8;
	int v1 = u << 3; // u * 8
	int v2 = (u << 5) - (u << 2); // u * 28

	int x = 15213;
	int x1 = x >> 1;
	int x2 = x >> 4;
	int x3 = x >> 8;

	printf("w1 is %u\n", w1);
	printf("w2 is %u\n", w2);

	decToBinary(w1);
	decToBinary(w2);

	printf("y1 is %d\n", y1);
	printf("y2 is %u\n", y2);

	decToBinary(y1);
	decToBinary(y2);

	printf("v1 is %d\n", v1);
	printf("v2 is %d\n", v2);

	decToBinary(x);
	decToBinary(x1);
	decToBinary(x2);
	decToBinary(x3);

	return 0;
}
