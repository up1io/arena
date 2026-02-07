#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
  uint8_t  *buf;
  size_t   cap;
  size_t   offset;
} arena_t;

arena_t arena_create(size_t capacity)
{
  arena_t a;
  a.buf = (uint8_t *)malloc(capacity);
  a.cap = capacity;
  a.offset = 0;
  return a;
}

void *arena_alloc(arena_t *arena, size_t size)
{
  size_t aligned = (arena->offset + 7) & ~(size_t)7;
  if (aligned + size > arena->cap) {
    fprintf(stderr, "Arena out of memory!\n");
    return NULL;
  }
  void *ptr = arena->buf + aligned;
  arena->offset = aligned + size;
  return ptr;
}
 
void arena_reset(arena_t *arena)
{
  arena->offset = 0;
}

void arena_destroy(arena_t *arena)
{
  free(arena->buf);
  arena->buf = NULL;
  arena->cap = 0;
  arena->offset = 0;
}

typedef struct {
    char *description;
} data_t;

typedef struct {
    data_t *data;
} item_t;

int main(void)
{ 
  arena_t arena = arena_create(4096);

  item_t *item = arena_alloc(&arena, sizeof(item_t));
  data_t *data = arena_alloc(&arena, sizeof(data_t));

  data->description = "hello world";
  item->data = data;

  printf("arena %s", item->data->description);

  arena_destroy(&arena);
}
