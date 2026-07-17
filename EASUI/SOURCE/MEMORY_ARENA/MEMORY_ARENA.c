#include "MEMORY_ARENA.h"



MARENA PROGRAM_ARENA;



// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! AI WRITEN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void INIT_MEMORY_AREMA(size_t DEFAULT_SIZE)
{

        PROGRAM_ARENA.HEAD = NULL;
        PROGRAM_ARENA.DEFAULT_SIZE = DEFAULT_SIZE;

}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! AI WRITEN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void* MEMORY_ARENA_ALLOC(size_t SIZE)
{

        size_t ALIGNMENT = 8;
        size_t ALIGNED_OFFSET = 0;



        if (PROGRAM_ARENA.HEAD != NULL)
        {

                ALIGNED_OFFSET = (PROGRAM_ARENA.HEAD->OFFSET + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);

        }

        // 2. If no block exists, or the allocation does not fit, create a new block
        if (PROGRAM_ARENA.HEAD == NULL || (ALIGNED_OFFSET + SIZE > PROGRAM_ARENA.HEAD->CAPACITY)) {

                // Choose between the default block size or the massive requested size
                size_t BLOCK_SIZE = PROGRAM_ARENA.DEFAULT_SIZE;


                if (SIZE > BLOCK_SIZE)
                {
                        BLOCK_SIZE = SIZE;
                }

                // Allocate block metadata and the memory payload together in one shot
                MARENA_BLOCK* NEW_BLOCK = (MARENA_BLOCK*)malloc(sizeof(MARENA_BLOCK) + BLOCK_SIZE);
                if (!NEW_BLOCK) return NULL;

                NEW_BLOCK->CAPACITY = BLOCK_SIZE;
                NEW_BLOCK->OFFSET = 0;

                // Push new block to the head of the global chain
                NEW_BLOCK->NEXT = PROGRAM_ARENA.HEAD;
                PROGRAM_ARENA.HEAD = NEW_BLOCK;

                ALIGNED_OFFSET = 0;

        }



        void* ALLOCATED_PTR = &PROGRAM_ARENA.HEAD->DATA[ALIGNED_OFFSET];

        PROGRAM_ARENA.HEAD->OFFSET = ALIGNED_OFFSET + SIZE;


        return ALLOCATED_PTR;

}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! AI WRITEN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void FREE_MEMORY_ARENA(void)
{
        MARENA_BLOCK* CURRENT_NODE = PROGRAM_ARENA.HEAD;

        while (CURRENT_NODE != NULL)
        {

                // Cast the void* back to MARENA_BLOCK* to step to the next link
                MARENA_BLOCK* NEXT_NODE = (MARENA_BLOCK*)CURRENT_NODE->NEXT;

                free(CURRENT_NODE);

                CURRENT_NODE = NEXT_NODE;

        }


        PROGRAM_ARENA.HEAD = NULL;
}
