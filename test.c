#include <string.h>
#include "Linear/arena.h"
#include "../Testing/ctf.h"

#define ARENA_SIZE 10000
static LinearArena arena = {0};

#define alloc(size) linear_arena_alloc(&arena,size)

CTF_TEST(New)
{
    linear_arena_reset(&arena);
    const char* key = "Example String";
    char* cpy = alloc(sizeof(key));
    strcpy(cpy, key);
    CTF_ASSERT(strcmp(cpy,key) == 0);
    CTF_PASS();
}

#define range(v,a,b) v = a; v < b; v++ 

CTF_TEST(Fill)
{
    linear_arena_reset(&arena);
    const char* key = "Example String";
    
    for (int range(i,0,ARENA_SIZE))
    {
        char* cpy = alloc(sizeof(key));
        if (!cpy)
        {
            CTF_LOG("Filled on %d iteration.",i);
            break;
        }
        strcpy(cpy, key);
        CTF_ASSERT(strcmp(cpy,key) == 0);
    }
    CTF_PASS();
}

CTF_TEST(Assorted)
{
    linear_arena_reset(&arena);
    int* a = alloc(sizeof(int));
    *a = 40;
    double* b = alloc(sizeof(double));
    *b = 3.141545;
    CTF_LOG("%d,%f",*a,*b);
    CTF_ASSERT(*b == 3.141545);
    CTF_ASSERT(*a == 40);
    CTF_PASS();
}

CTF_SUITE(
    Arena,
    {
        CTF_LINK(Arena, New);
        CTF_LINK(Arena, Fill);
        CTF_LINK(Arena, Assorted);
    }
)

int main(int argc, char** argv)
{
    arena = linear_arena_new(ARENA_SIZE);

    CTF_PROCESS_INIT();
    CTF_SUITE_RUN(Arena);
    CTF_PROCESS_EXIT();

    linear_arena_free(&arena);
    return 0;
}