#ifndef _LINEAR_ARENA_H
#define _LINEAR_ARENA_H

#include <stddef.h>

typedef struct
{
    unsigned char *pool;
    size_t offset;
    size_t size;
} LinearArena;

LinearArena linear_arena_new(size_t size);

/* Returns NULL if it cannot return a block that size */
void *linear_arena_alloc(LinearArena *arena, size_t bytes);

void linear_arena_reset(LinearArena *arena);

void linear_arena_free(LinearArena *arena);

#endif /*_LINEAR_ARENA_H*/