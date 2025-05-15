#include "arena.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*
typedef struct
{
    unsigned char *pool;
    size_t offset;
    size_t size;
} LinearArena;
*/

LinearArena linear_arena_new(size_t size)
{
    LinearArena arena = {(unsigned char *)malloc(size), 0, size};
    return arena;
}

/* Returns NULL if it cannot return a block that size */
void *linear_arena_alloc(LinearArena *arena, size_t bytes)
{
    const size_t alignment = sizeof(void*); // Safe alignment

    size_t aligned_offset = (arena->offset + (alignment - 1)) & ~(alignment - 1);

    if (aligned_offset > arena->size || bytes > arena->size - aligned_offset)
    {
        return NULL;
    }

    void *memory = arena->pool + aligned_offset;
    arena->offset = aligned_offset + bytes;
    return memory;
}


void linear_arena_reset(LinearArena *arena)
{
    memset(arena->pool, 0, arena->size);
    arena->offset = 0;
}

void linear_arena_free(LinearArena *arena)
{
    free(arena->pool);
    arena->offset = arena->size = 0;
    arena->pool = NULL;
}