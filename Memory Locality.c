/*
 * Memory Locality.c
 *
 *  Created on: 11 May 2021
 *      Author: Grant
 */

#define M 500
#define N 500

#include <time.h>

int sum_array_rows(int a[M][N])
{
	int i, j, sum = 0;

	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			sum += a[j][i];

	return sum;
}

int sum_array_rows_locality(int a[M][N])
{
	int i, j, sum = 0;

	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			sum += a[i][j];

	return sum;
}

int main()
{
	int a[M][N];

	clock_t start = clock();

	int b;

	for (int i = 0; i < 1000; i++)
	{
		//b = sum_array_rows(a);      //1.015
		//b = sum_array_rows_locality(a);  //0.908
	}

	clock_t stop = clock();
	double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
	printf("Time elapsed in ms: %f", elapsed);

	return 0;
}
