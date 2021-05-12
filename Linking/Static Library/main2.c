#include <stdio.h>
#include <unistd.h>

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

int main()
{
 addvec(x, y, z, 2);
 printf("z = [%d %d]\n", z[0], z[1]);
 sleep(5);
 return 0;
}