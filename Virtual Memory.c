#include <stdio.h>
#include <stdint.h>

void to_binary(long n)
{
    char str[49], *ptr = str + 1;
    str[0] = '\n';
    do{
        *ptr++ = '0' + (n&1);
    } while(n >>= 1);
    while(ptr > str)
        putc(*--ptr, stdout);
}

void address(long n)
{
    char str[49], *ptr = str + 1;
    str[0] = '\n';
    do{
        *ptr++ = '0' + (n&1);
    } while(n >>= 1);
    
    printf("TLBT: ");
    while(ptr > str + 16)
    {
    	putc(*--ptr, stdout);
    }
    printf("\n");

    printf("TLBI: ");
    while(ptr > str + 12)
    {
    	putc(*--ptr, stdout);
    }
    printf("\n");

    printf("VPO: ");
    while(ptr > str)
    {
    	putc(*--ptr, stdout);
    }
    printf("\n");
}

int main()
{
	int x = 11;
	int* ptr = &x;
	
	printf("Virtual Address (Hexadecimal) is: %p\n", ptr);
	long num = (long) ptr;
	printf("Virtual Address (Integer) is: %ld\n", num);

	to_binary(num);	
	printf("\n");
	address(num);
	
	sleep(5);

	return 0;
}
