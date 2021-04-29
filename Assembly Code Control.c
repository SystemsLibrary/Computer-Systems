/*
 * Assembly Code Control.c
 *
 *  Created on: 28 Apr 2021
 *      Author: Grant
 */

int gt (long x, long y)
{
	// %rdi - x, %rsi - y, %rax - return value
	return x > y; //cmpq   %rsi, %rdi
				  //setg   %al
				  //movcbl %al, %eax
			      //ret
}

long absdiff(long x, long y)
{
	long result;

	// %rdi - x, %rsi - y, %rax - return value
	if (x > y)				//cmpq %rsi, %rdi
						    //jle  .L4
		result = x - y;	    //movq %rdi, %rax
							//subq %rsi, %rax
							//ret
	else					//L4:
		result = y - x;	    //movq %rsi, %rax
							//subq %rdi, %rax
							//ret

	return result;
}

long absdiffshort(long x, long y)
{
	long result = x>y ? x - y : y-x; //cmpq %rsi, %rdi
									 //jle  .L6
									 //movq %rdi, %rax
								     //subq %rsi, %rax
									 //ret
									 //.L6:
								     //movq %rsi, %rax
									 //subq %rdi, %rax
									 //ret
	return result;
}

long pcount_do(unsigned long x)
{
	//%rdi - x, %rax - result
	long result = 0;        //movl $0, %eax
	do {					//.L2:
		result += x & 0x1;  //movq %rdi, %rdx
							//andl $1,   %edx
							//addq %rdx, %rax
		x >>= 1;			//shrq %rdi
	} while (x);			//jne  .L2
	return result;			//rep: ret
}

long pcount_while(unsigned long x)
{
	//%rdi - x, %rax - result
	long result = 0;        //movl $0, %eax
	while (x) 				//.L11:
							//testq %rdi, %rdi
	{						//je .L13:
		result += x & 0x1;  //movq %rdi, %rdx
							//andl $1,   %edx
							//addq %rdx, %rax
		x >>= 1;			//shrq %rdi
							//jmp .L11:
	}
	return result;			//L13:
							//ret
}

#define WSIZE 8*sizeof(int)
long pcount_for(unsigned long x)
{
	unsigned i;
	long result = 0; //movl $0, %eax
					 //movl $0, %ecx
	for (i = 0; i < WSIZE; i++) //.L15
								//cmpl $31, %ecx
								//ja .L17
	{
		unsigned bit = (x >> i) & 0x1;		//movq %rdi, %rdx
											//shrq %cl, %rdx
											//andl $1, %edx
		result += bit;						//addq %rdx, %rax
											//addl $1, ecx
											//jmp .L15
	}
	return result; //.L17:
				   //ret
}

long switch_eg(long x, long y, long z)
{
	long w = 1;

	//%rdi - x, %rsi - y, %rdx - z, %rax - return value

	switch(x) {
	// .section .rodata
	//     .align
	// .L4:
	//    .quad .L8 #x = 0
	//    .quad .L3 #x = 1
	//    .quad .L5 #x = 2
	//    .quad .L9 #x = 3
	//    .quad .L8 #x = 4
	//    .quad .L7 #x = 5
	//    .quad .L7 #x = 6

	case 1:     //.L3
		w = y*z;//movq %rsi, %rax
				//imulq %rdx, %rax
		break;
	case 2:     //.L5
		w = y/z;//movq %rsi, %rax
		        //cqto
		        //idivq %rcx
		        //jmp .L6
	case 3:    //.L9
		w += z;//movl $1, %eax
			   //.L6
		       //addq %rcx, %rax
		break;
	case 5:    //.L7
	case 6:	   //.L7
		w -= z;//movl $1, %eax
			   //subq %rdx, %rax
		break;
	default:   //.L8:
		w = 2; //     movl $2, %eax
	}
	return w; //ret
}

int main()
{
	long a = 5;
	long b = 1;

	int c = gt(a, b);

	long d = absdiff(a, b);
	long e = absdiffshort(a, b);

	unsigned long g = 5;
	long h = pcount_do(g);
	long i = pcount_while(g);
	long j = pcount_for(g);

	long p = 1;
	long q = 2;
	long r = 3;
	long m = switch_eg(p, q, r);

	return 0;
}
