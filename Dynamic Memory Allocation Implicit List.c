/*
 * Dynamic Memory Allocation Implicit List.c
 *
 *  Created on: 17 May 2021
 *      Author: Grant
 */

#include <stdio.h>
#include <stdlib.h>

int n = 400;

int* search (int* start, int* end, int len)
{
	int* p = start;
	while ((p < end) && ((*p & 1) || (*p <= len)))
	{
		if (p + (*p & -2) > end)
			break;

		if ((*p & 1) == 0)
			break;

		p = p + (*p & -2);
	}

	printf("Free block position: %p\n", p);

	return p;
}

int* allocate_block_new(int* start, int len) {
	int* p = search (start, start + 400, len);

	int newsize = ((len + 1) >> 1) << 1; // round up to even
	*p = newsize | 1; // set new length

	printf("Free block: %p\n\n", p);
	return p;
}

void free_block(int* p, int last_block) {
	*p = *p & -2; // clear allocated flag
	int* next = p + *p; // find next block

	if (last_block == 1)
		return;

	if ((*next & 1) == 0)
	{
		*p = *p + *next; // add to this block if
	}
}

int main()
{
	int* p = (int *) malloc(n * sizeof(int));
	if (p == NULL) {
		perror("malloc");
		exit(0);
	}

	printf("Starting Position: %p\n", p);
	printf("Starting Position: %p\n", p + 1);
	printf("Starting Position: %p\n", p + 2);
	printf("Ending Position: %p\n", p + 400);

	int* p1 = allocate_block_new(p, 4);
	int* p2 = allocate_block_new(p, 2);
	int* p3 = allocate_block_new(p, 4);
	int* p4 = allocate_block_new(p, 4);

	search (p, p + n, 4);

	free_block(p1, 0);

	printf("Block is freed\n\n");

	search (p, p + n, 4);

	free(p);

	return 0;
}
