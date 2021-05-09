/*
 * Assembly Code Security.c
 *
 *  Created on: 9 May 2021
 *      Author: Grant
 */

#include <stdio.h>

char big_array[1L<<24];
char huge_array[1L<<30];

int global = 0;

int useless() { return 0; }

typedef struct
{
	int a[2];
	double d;
} struct_t;

double fun(int i)
{
	volatile struct_t s;
	s.d = 3.14;
	s.a[i] = 11;
	return s.d;
}

void echo()
{
	char buf[4];
	gets(buf);
	puts(buf);
}

void secure_echo()
{
	char buf[4];
	fgets(buf, 4, stdin);
	puts(buf);
}

void call_echo()
{
	secure_echo();
}

union dw
{
	unsigned char c[8];
	unsigned short s[4];
	unsigned int i[2];
	unsigned long l[1];
};

int main()
{
	printf("%ld bytes per pointer\n", sizeof(void *));

	void *p1, *p2, *p3, *p4;
	int local = 0;
	p1 = malloc(1L << 21);
	p2 = malloc(1L << 8);
	p3 = malloc(1L << 16);
	p4 = malloc(1L << 8);

	printf("local: %p\n", &local);
	printf("p1: %p\n", &p1);
	printf("p2: %p\n", &p2);
	printf("p3: %p\n", &p3);
	printf("p4: %p\n", &p4);
	printf("big_array: %p\n", &big_array);
	printf("huge_array: %p\n", &huge_array);
	printf("main: %p\n", main);
	printf("useless: %p\n", useless);

	printf("fun: %f\n", fun(2));

	//call_echo();

	union dw a;

	int j;
	for (j = 0; j < 8; j++)
	{
		a.c[j] = 0xf0 + j;
	}

	printf("Characters 0-7 == [0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x]\n",
	 a.c[0], a.c[1], a.c[2], a.c[3],
	 a.c[4], a.c[5], a.c[6], a.c[7]);

	printf("Shorts 0-3 == [0x%x,0x%x,0x%x,0x%x]\n",
	 a.s[0], a.s[1], a.s[2], a.s[3]);

	printf("Ints 0-1 == [0x%x,0x%x]\n",
	 a.i[0], a.i[1]);

	printf("Long 0 == [0x%lx]\n",
	 a.l[0]);
}
