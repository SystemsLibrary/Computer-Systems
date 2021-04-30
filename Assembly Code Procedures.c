/*
 * Assembly Code Procedures.c
 *
 *  Created on: 30 Apr 2021
 *      Author: Grant
 */

long mult2(long a, long b)					//400550 <multstore>:
{											//400550: mov  %rdi,%rax
	long s = a * b;							//400553: imul %rsi,%rax
	return s;								//400557: retq
}

void multstore (long x, long y, long *dest) //400540 <multstore>:
{											//400540: push %rbx
											//400541: mov  %rdx, %rbx
	long t = mult2(x, y);					//400544: callq 400550 <mult2>
	*dest = t;								//400549: mov  %rax, (%rbx)
											//40054c: pop  %rbx
											//40054d: retq
}

long incr (long *p, long val)
{
	// %rdi - p, %rsi - val, y, %rax - x, return value
	long x = *p;      //movq (%rdi), %rax
	long y = x + val; //addq %rax, %rsi
	*p = y;           //movq %rsi, (%rdi)
	return x;		  //ret
}

long call_incr ()
{								//subq $16, %rsp
	long v1 = 15123;			//movq $15123, 8(%rsp)
								//leaq 8(%rsp), %rdi
	long v2 = incr(&v1, 3000);  //movl $3000, %esi
								//leaq 8(%rsp), %rdi
								//call incr
	return v1+v2;				//addq 8(%rsp), %rax
								//addq $16, %rsp
								//ret
}

long call_incr2 (long x)
{								//pushq %rbx
								//subq $16, %rsp
								//movq %rdi, %rbx
	long v1 = 15123;			//movq $15123, 8(%rsp)
								//leaq 8(%rsp), %rdi
	long v2 = incr(&v1, 3000);  //movl $3000, %esi
								//call incr
	return x+v2;				//addq %rbx, %rax
								//addq $16, %rsp
								//popq %rbx
								//ret
}

long pcount_r(unsigned long x)
{											//movl   $0, %eax
	if (x == 0)								//testq  %rdi, %rdi
											//jne     .L16
		return 0;							//movl   $0, %eax
											//ret
	else									//L16:
		return (x & 1)						//pushq  %rbx
											//movq   %rdi, %rbx
											//andl   $1, %ebx
											//shrq   %rdi
				+ pcount_r(x >> 1);			//call   pcount_r
											//addq   %rbx, %rax
											//popq   %rbx
}

int main()
{
	long a = 5;
	long b = 1;
	long *c;

	multstore(a, b, c);

	call_incr2(a);

	unsigned long g = 5;
	long h = pcount_r(g);

	return 0;
}
