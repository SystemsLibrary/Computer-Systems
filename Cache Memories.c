/*
 * Cache Memories.c
 *
 *  Created on: 11 May 2021
 *      Author: Grant
 */

#include <time.h>

#define n 100

void matrix_multiplication_jki(int a[n][n], int b[n][n])
{
	int i, j, k, r;
	int c[n][n];

	for (j=0; j<n; j++) {
		for (k=0; k<n; k++) {
			r = b[k][j];
			for (i=0; i<n; i++)
				c[i][j] += a[i][k] * r;
		}
	}
}

void matrix_multiplication_ijk(int a[n][n], int b[n][n])
{
	int i, j, k, sum;
	int c[n][n];

	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			sum = 0.0;
			for (k=0; k<n; k++)
				sum += a[i][k] * b[k][j];
			c[i][j] = sum;
		}
	}
}

void matrix_multiplication_kij(int a[n][n], int b[n][n])
{
	int i, j, k, r;
	int c[n][n];

	for (k=0; k<n; k++) {
		for (i=0; i<n; i++) {
			r = a[i][k];
			for (j=0; j<n; j++)
				c[i][j] += r * b[k][j];
		}
	}
}

void mmm(double *a, double *b, double *c) {
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++)
				c[i*n + j] += a[i*n + k] * b[k*n + j];
}

void mmm_block(double *a, double *b, double *c, int B) {
	int i, j, k;
	int i1, j1, k1;
	for (i = 0; i < n; i+=B)
		for (j = 0; j < n; j+=B)
			for (k = 0; k < n; k+=B)
				/* B x B mini matrix multiplications */
				for (i1 = i; i1 < i+B; i1++)
					for (j1 = j; j1 < j+B; j1++)
						for (k1 = k; k1 < k+B; k1++)
							c[i1*n+j1] += a[i1*n + k1]*b[k1*n + j1];

}

int main()
{
	int a[n][n];
	int b[n][n];

	double a1[n][n];
	double b1[n][n];
	double c1[n][n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = 1;
			b[i][j] = 1;

			a1[i][j] = 1.0;
			b1[i][j] = 1.0;
		}
	}

	clock_t start = clock();

	for (int k = 0; k < 100; k++)
	{
		//matrix_multiplication_jki(a, b); //0.678
		//matrix_multiplication_ijk(a, b); //0.458
		//matrix_multiplication_kij(a, b); //0.453

		//mmm(a1, b1, c1); //0.75
		//mmm_block(a1, b1, c1, 20); //0.555
	}

	clock_t stop = clock();
	double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
	printf("Time elapsed in ms: %f", elapsed);

	return 0;
}
