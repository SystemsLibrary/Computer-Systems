/*
 * Assembly Code Data.c
 *
 *  Created on: 8 May 2021
 *      Author: Grant
 */

#include <stdio.h>

#define ZLEN 5

typedef int zip_dig[ZLEN];

zip_dig cmu = {1, 5, 2, 1, 3};
zip_dig mit = {0, 2, 1, 3, 9};
zip_dig ucb = {9, 4, 7, 2, 0};

#define PCOUNT 4

zip_dig pgh[PCOUNT] = {{1, 5, 2, 0, 6},
					   {1, 5, 2, 1, 3},
					   {1, 5, 2, 1, 7},
					   {1, 5, 2, 2, 1}};

struct c
{
	short i;
	int v;
	short j;
} c_array[10];

short get_j(int idx)
{
	return c_array[idx].j; //leaq   (%rdi, %rdi, 2),%rax
						   //movzwl a+8(,%rax,4),%eax
}

int get_digit(zip_dig z, int digit)
{
	//%rdi = z
	//%rsi = digit
	return z[digit]; //movl (%rdi,%rsi,4), %eax
}

int *get_pgh_zip(int index)
{
	//%rdi = index
	return pgh[index]; //leaq (%rdi,%rdi,4),%rax     5 * index
					   //leaq pgh(,%rax,4),%rax      pgh + (20 * index)
}

int get_pgh_digit(int index, int dig)
{
	return pgh[index][dig]; //leaq (%rdi,%rdi,4), %rax    5*index
						    //addl %rax, %rsi             5*index+dig
						    //movl pgh(,%rsi,4), %eax     M[pgh + 4*(5*index+dig)]
}

void zincr(zip_dig z)
{
	unsigned int i;

	//%rdi = z
	for(i = 0; i < ZLEN; i++) //movl $0, %eax # i = 0
							  //jmp. L3
							  //.L4:
		z[i]++;				  //addl $1, (%rdi, %rax, 4)
							  //addq $1, %rax
							  //.L3:
							  //cmpq $4, %rax
							  //jbe .L4
							  //rep; ret
}

#define UCOUNT 3

int *univ[UCOUNT] = {mit, cmu, ucb};

int get_univ_digit(unsigned int index, unsigned int digit)
{
	return univ[index][digit]; //salq $2, %rsi                4*digit
							   //addq univ(,%rdi,8), %rsi     p = univ[index] + 4 * digit
							   //movl (%rsi), %eax            return *p
}

#define N 16
typedef int fix_matrix[N][N];
int fix_ele(fix_matrix a, unsigned int i, unsigned int j)
{
	//a in %rdi, i in %rsi, j in %rdx
	return a[i][j]; //salq $6, %rsi     64*i
					//addq %rsi,%rdi    a+64*i
					//movl (%rdi,%rdx,4), %eax  M[a + 64*i + 4*j]
					//ret
}

#define IDX(n, i, j) ((i)*(n) + (j))
int vec_ele(unsigned int n, int* a, unsigned int i, unsigned int j)
{
	return a[IDX(n, i, j)];
}

int var_ele(unsigned int n, int a[n][n], unsigned int i, unsigned int j)
{
	// n in %rdi, a in %rsi, i in %rdx, j in %rcx
	return a[i][j]; //imulq %rdx, %rdi        n*i
					//leaq  (%rsi,%rdi,4),%rax   a+4*n*i
					//movl  (%rax,%rcx,4),%eax   a+4*n*i+4*j
					//ret
}

struct rec
{
	int a1[2];
	int b1;
	int i;
	int c;
	int d;
	int a2[3];
	int e;
};

struct new_rec
{
	char c;
	int i[2];
	double v;
};

struct new_new_rec
{
	double v;
	int i[2];
	char c;
};

struct s4
{
	char c;
	int i;
	char d;
};

struct s5
{
	int i;
	char c;
	char d;
};

struct s6
{
	char c;
	char d;
	int i;
};

struct new
{
	int a[4];
	unsigned int i;
	struct new* next;
};

int *get_ap(struct new* r, unsigned int idx)
{
	// r in %rdi, idx in %rsi
	return &r->a[idx]; //leaq (%rdi,%rsi,4), %rax
					   //ret
}

void set_val(struct new* r, unsigned int val)
{
	// %rdi - r, %rsi - val
	while (r)
	{					//.L11:
		int i = r->i;	//movsql 16(%rdi),%rax i = M[r+16]
		r->a[i] = val;	//movl   %esi,(%rdi,%rax,4) M[r+4*i]=val
		r = r->next;	//movq   24(%rdi),%rdi r=M[r+24]
	}					//testq  %rdi,%rdi
						//jne    .L11
}

int main()
{
	printf("cmu: %p, %p, %p, %p\n", &cmu[0], &cmu[1], &cmu[2], &cmu[3]);
	printf("mit: %p, %p, %p, %p\n", mit, mit + 1, mit + 2, mit + 3);
	printf("ucb: %p, %p, %p, %p\n", ucb, ucb + 1, ucb + 2, ucb + 4);

	int a = get_digit(cmu, 0);

	printf("cmu[0]: %d\n", a);

	zincr(cmu);

	printf("pgh: %p, %p, %p, %p, %p\n", &pgh[0][0], &pgh[0][1], &pgh[0][2], &pgh[0][3], &pgh[0][4]);
	printf("pgh: %p, %p, %p, %p, %p\n", &pgh[1][0], &pgh[1][1], &pgh[1][2], &pgh[1][3], &pgh[1][4]);
	printf("pgh: %p, %p, %p, %p, %p\n", &pgh[2][0], &pgh[2][1], &pgh[2][2], &pgh[2][3], &pgh[2][4]);
	printf("pgh: %p, %p, %p, %p, %p\n", &pgh[3][0], &pgh[3][1], &pgh[3][2], &pgh[3][3], &pgh[3][4]);
	printf("\n");
	printf("pgh: %p, %p, %p, %p, %p\n", pgh[0], pgh[0] + 1, pgh[0] + 2, pgh[0] + 3, pgh[0] + 4);
	printf("pgh: %p, %p, %p, %p, %p\n", pgh[1], pgh[1] + 1, pgh[1] + 2, pgh[1] + 3, pgh[1] + 4);
	printf("pgh: %p, %p, %p, %p, %p\n", pgh[2], pgh[2] + 1, pgh[2] + 2, pgh[2] + 3, pgh[2] + 4);
	printf("pgh: %p, %p, %p, %p, %p\n", pgh[3], pgh[3] + 1, pgh[3] + 2, pgh[3] + 3, pgh[3] + 4);
	printf("\n");

	int *b = get_pgh_zip(0);

	int c = get_pgh_digit(0, 0);

	printf("univ: %p, %p, %p, %p, %p\n", &univ[0][0], &univ[0][1], &univ[0][2], &univ[0][3], &univ[0][4]);
	printf("univ: %p, %p, %p, %p, %p\n", &univ[1][0], &univ[1][1], &univ[1][2], &univ[1][3], &univ[1][4]);
	printf("univ: %p, %p, %p, %p, %p\n", &univ[2][0], &univ[2][1], &univ[2][2], &univ[2][3], &univ[2][4]);

	int d = get_univ_digit(0, 0);

	int matrix1[16][16] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
						   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	int e = fix_ele(matrix1, 0, 0);

	int matrix2[5][5] = {{1, 1, 1, 1, 1},
						{1, 1, 1, 1, 1},
						{1, 1, 1, 1, 1},
						{1, 1, 1, 1, 1},
						{1, 1, 1, 1, 1}};

	int g = vec_ele(4, matrix2, 0, 0);
	printf("%d\n", g);

	int h = var_ele(4, matrix2, 0, 0);
	printf("%d\n", h);

	struct rec rec1;

	printf("rec1: %p, %p, %p, %p, %p, %p, %p\n", &rec1.a1, &rec1.b1, &rec1.i, &rec1.c, &rec1.d, &rec1.a2, &rec1.e);

	struct new_rec rec2;

	printf("rec2: %p, %p, %p\n", &rec2.c, &rec2.i, &rec2.v);

	struct new_new_rec rec3;

	printf("rec3: %p, %p, %p\n", &rec3.v, &rec3.i, &rec3.c);

	struct new_new_rec rec_array[5];

	printf("rec_array[0]: %p, %p, %p\n", &rec_array[0].v, &rec_array[0].i, &rec_array[0].c);
	printf("rec_array[1]: %p, %p, %p\n", &rec_array[1].v, &rec_array[1].i, &rec_array[1].c);

	struct s4 v1;
	struct s5 v2;
	struct s6 v3;

	printf("s4: %p, %p, %p\n", &v1.c, &v1.i, &v1.d);
	printf("s5: %p, %p, %p\n", &v2.i, &v2.c, &v2.d);
	printf("s6: %p, %p, %p\n", &v1.c, &v1.d, &v1.i);

	struct new set1;

	int* set1_output = get_ap(&set1, 0);

	set1.i = 0;
	set1.next = NULL;
	set_val(&set1, 5);

	get_j(1);

	return 0;
}
