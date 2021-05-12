#include <stdio.h>
#include <unistd.h>

int sum(int *a, int n);

int array[2] = {1, 2};

int x = 15;

int main()
{
	int val = sum(array, 2);
	printf("%d\n", val);
	sleep(5);
 	return val;
}