# Arena (WIP)

This repository explores the concept of arenas. The implementation is done in C.

## Foundation
 
As far as I understand, an arena, also called a line allocation, is a certain memory space that is allocated once initially, and all the data is placed inside. 
The benefit is having a central place to allocate and free, i.e., "allocate once, free once."

### Problem

```c
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char *description;
} data_t;

typedef struct {
    data_t *data;
} item_t;

int main(void)
{
    item_t *v = malloc(sizeof(item_t));
    v->data = malloc(sizeof(data_t));
    v->data->description = "hello world";

    printf("%s", v->data->description);

    free(v->data); // Manual freeing
    free(v);
}
```
If we forget or comment for demo purposes `free(v->data);` this causes some leaks. 

We can confirm this with valgrind:

```
hello world==112372==
==112372== HEAP SUMMARY:
==112372==     in use at exit: 8 bytes in 1 blocks
==112372==   total heap usage: 3 allocs, 2 frees, 1,040 bytes allocated
==112372==
==112372== LEAK SUMMARY:
==112372==    definitely lost: 8 bytes in 1 blocks
==112372==    indirectly lost: 0 bytes in 0 blocks
==112372==      possibly lost: 0 bytes in 0 blocks
==112372==    still reachable: 0 bytes in 0 blocks
==112372==         suppressed: 0 bytes in 0 blocks
==112372== Rerun with --leak-check=full to see details of leaked memory  
```

## Arena benefits 

```
arena hello world==31576==
==31576== HEAP SUMMARY:
==31576==     in use at exit: 0 bytes in 0 blocks
==31576==   total heap usage: 2 allocs, 2 frees, 5,120 bytes allocated
==31576==
==31576== All heap blocks were freed -- no leaks are possible
==31576==
==31576== For lists of detected and suppressed errors, rerun with: -s
==31576== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
