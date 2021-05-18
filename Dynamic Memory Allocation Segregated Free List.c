/*
 * Dynamic Memory Allocation Aggregated Free List.c
 *
 *  Created on: 18 May 2021
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>

int n = 100;

void free_list_block(int* start, int position, int len)
{
	int point = position * len;
	int* p = start + point;

	if (*(p + 1) != 0 || *(p + 2) != 0)
	{
		printf("The block is free!\n");
		return;
	}

	int next = *(start + 1);
	*(start + 1) = *p;
	*(p + 1) = next;
	*(p + 2) = 0;
	*(start + next * len + 2) = *p;

	for (int l = 0; l < n; l++)
	{
		printf("value: %d\n", *(start + l));
	}
}

void allocate_list_block(int* start, int position, int len)
{
	int point = position * len;
	int* p = start + point;

	int next = *(p + 1);
	int previous = *(p + 2);

	int point1 = previous * len;
	int* p1 = start + point1;
	*(p1 + 1) = next;

	int point2 = next * len;
	int* p2 = start + point2;
	*(p2 + 2) = previous;

	for (int i = 1; i < len; i++)
	{
		*(p + i) = 0;
	}

	for (int l = 0; l < n; l++)
	{
		//printf("value: %d\n", *(start + l));
	}
}

void create_block_new(int* start, int* end, int len) {
	int* p = start;
	int newsize = ((len + 1) >> 1) << 1; // round up to even
	int length = newsize | 1; // set new length

	for (int k = 0; k < n; k++)
	{
		*(p + k) = 0;
	}

	int j = 0;
	for (int i = 0; i < n; i += len)
	{
		*(p + i) = j;
		*(p + i + 1) = j + 1;
		*(p + i + 2) = j - 1;
		j++;
	}

	for (int l = 0; l < n; l++)
	{
		//printf("value: %d\n", *(p + l));
	}
}

int main()
{
	int size = 4;

	int* p = (int *) malloc(n * sizeof(int));
	if (p == NULL) {
		perror("malloc");
		exit(0);
	}

	printf("Starting Position: %p\n", p);
	printf("Starting Position: %p\n", p + 1);
	printf("Starting Position: %p\n", p + 2);
	printf("Ending Position: %p\n", p + n);

	create_block_new(p, p + n, 4);

	allocate_list_block(p, 5, 4);

	free_list_block(p, 5, 4);

	free(p);

	return 0;
}
