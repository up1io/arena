#include <stdlib.h>
#include <stdio.h>

typedef struct arena_t {
  void *data;
  int used;
  int capacity;
} arena_t;

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

    // free(v->data);
    free(v);
}
