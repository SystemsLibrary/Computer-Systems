#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

int main()
{
 int *p = malloc(32);
 free(p);
 sleep(5);
 return(0);
}