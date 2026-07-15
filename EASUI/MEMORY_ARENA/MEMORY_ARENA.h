#define MEMORY_ARENA
#ifdef MEMORY_ARENA



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>




typedef struct MARENA_BLOCK
{

        void* NEXT;
        size_t CAPACITY;
        size_t OFFSET;
        uint8_t DATA[];

}MARENA_BLOCK;


typedef struct
{

        MARENA_BLOCK* HEAD;
        size_t DEFAULT_SIZE;

}
MARENA;





void INIT_MEMORY_AREMA(size_t DEFAULT_SIZE);


void* MEMORY_ARENA_ALLOC(size_t SIZE);


void FREE_MEMORY_ARENA(void);



#endif
