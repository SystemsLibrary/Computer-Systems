/*
 * Little Endian.c
 *
 *  Created on: 26 Apr 2021
 *      Author: Grant
 */

typedef unsigned char *pointer;

void show_bytes(pointer start, unsigned len)
{
	unsigned i;

	for (i = 0; i < len; i++)
	{
		printf("%p\t%.2x\n", start + i, start[i]);
	}

	printf("\n");
}

int main()
{
	int a = 15213;

	printf("a = 15213;\n");

	show_bytes((pointer) &a, sizeof(int));

	return 0;
}
