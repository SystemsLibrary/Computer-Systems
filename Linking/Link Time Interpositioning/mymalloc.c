#ifdef LINKTIME
#include <stdio.h>

void *__real_malloc(size_t size);
void __real_free(void *ptr);

void *__wrap_malloc(size_t size)
{
 void *ptr = __real_malloc(size); /* Call libc malloc */
 printf("malloc(%d) = %p\n", (int)size, ptr);
 return ptr;
}

void __wrap_free(void *ptr)
{
 __real_free(ptr); /* Call libc free */
 printf("free(%p)\n", ptr);
}
#endif