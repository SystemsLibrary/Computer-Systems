/*
 * Machine Code Basics.c
 *
 *  Created on: 28 Apr 2021
 *      Author: Grant
 */

long plus (long x, long y)
{
	return x + y; //leaq (%rdi, %rsi), %rax
				  //ret
}


void sumstore (long x, long y, long *dest)
{
	//t is register %rax
	//dest is register %rbx

	long t = plus(x, y); //pushq %rbx
						 //movq  %rdx, %rbx
						 //call  plus
	*dest = t;			 //movq  %rax, (%rbx)
						 //popq  %rbx
}

void swap (long *xp, long *yp)
{
	long t0 = *xp; //movq (%rdi), %rax
	long t1 = *yp; //movq (%rsi), %rdx
	*xp = t1;      //movq %rdx,   (%rdi)
	*yp = t0;      //movq %rax,   (%rsi)
}

long m12(long x)
{
	return x * 12; //leaq (%rdi, %rdi, 2), %rax
				   //salq $2, %rax
}

long arith(long x, long y, long z)
{
	long t1 = x + y;      //leaq (%rdi, %rsi), %rax
	long t2 = z + t1;	  //addq %rdx, %rax
	long t3 = x + 4;
	long t4 = y * 48;     //leaq (%rsi, %rsi, 2), %rdx
						  //salq $4, %rdx
	long t5 = t3 + t4;    //leaq 4(%rdi, %rdx), %rcx
	long rval = t2 * t5;  //imulq %rcx, %rax
	return rval;          //ret
}

int main()
{
	long a = 5;
	long b = 1;
	long *s;

	sumstore(a, b, s);

	long dt = 5;
	long et = 1;
	long *d = &dt;
	long *e = &et;
	swap(d, e);

	m12(a);

	long g = 1;
	long h = 2;
	long i = 3;
	long j = arith(g, h, i);

	return 0;
}
