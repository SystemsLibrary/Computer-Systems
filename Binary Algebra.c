/*
 * booleanalgebra.c
 *
 *  Created on: 23 Apr 2021
 *      Author: Grant
 */

int A = 60;
int B = 13;

int C = 98;
int D = 162;

short int x = 15213;
short int y = -15213;

short int TMin = -32768;
short int minus_one = -1;

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
	int AND = A&B;
	int OR = A|B;
	int NOT = ~A;
	int XOR = A^B;

	int INTEGER_LEFT_SHIFT_C = C << 3;
	int INTEGER_RIGHT_SHIFT_C = C >> 2;

	int INTEGER_LEFT_SHIFT_D = D << 3;
	int INTEGER_RIGHT_SHIFT_D = D >> 2;

	printf("A and B is %d\n", AND);
	printf("A or B is %d\n", OR);
	printf("Not A is %d\n", NOT);
	printf("A Xor B is %d\n", XOR);

	printf("Integer C left shift by 3 is %d\n", INTEGER_LEFT_SHIFT_C);
	printf("Integer C right shift by 2 is %d\n", INTEGER_RIGHT_SHIFT_C);

	printf("Integer D left shift by 3 is %d\n", INTEGER_LEFT_SHIFT_D);
	printf("Integer D right shift by 2 is %d\n", INTEGER_RIGHT_SHIFT_D);

	decToBinary(x);
	decToBinary(y);

	decToBinary(TMin);
	decToBinary(minus_one);

	return 0;
}
