#include "../../EASUI.h"




int SCREEN_ADD_ELEMENT(EASUI_SCREEN* SCREEN, void* ELEMENT);

unsigned short GET_LAST_ELEMENT_INDEX(EASUI_SCREEN* SCREEN, int* OFFSET);




int SET_NEW_EASUI_SCREEN(EASUI_SCREEN* SCREEN, const unsigned short MAX_ELEMENT_COUNT)
{

        // [NULL POINTER CHECKS]
        {

                if (SCREEN == NULL)
                {

                        LOG_EASUI_ERROR("FAILED TO SET NEW EASUI SCREEN : SCREEN POINTER IS NULL");


                        return EASUI_ERROR;

                }

        }


        // [SET BASE VALUES]
        {

                SCREEN->TYPE = EASUI_SCREEN_NUMBER;
                SCREEN->MAX_ELEMENT_COUNT = MAX_ELEMENT_COUNT;
                SCREEN->ADD_ELEMENT = SCREEN_ADD_ELEMENT;

        }


        // [ALLOCATE MEMORY FOR ELEMENT LIST]
        {

                SCREEN->ELEMENT_LIST = MEMORY_ARENA_ALLOC(sizeof(void*) * (MAX_ELEMENT_COUNT + 1));


                if (SCREEN->ELEMENT_LIST == NULL)
                {

                        LOG_EASUI_ERROR("FAILED TO SET NEW EASUI SCREEN : FAILED TO ALLOCATE MEMORY FOR ELEMENT LIST");


                        return EASUI_ERROR;

                }


                SCREEN->ELEMENT_LIST[0] = NULL;

        }


        return EASUI_OK;

}


int SCREEN_ADD_ELEMENT(EASUI_SCREEN* SCREEN, void* ELEMENT)
{

        int OFFSET;

        const unsigned short LAST_ELEMENT_INDEX = GET_LAST_ELEMENT_INDEX(SCREEN, &OFFSET);


        if (LAST_ELEMENT_INDEX + 1 > SCREEN->MAX_ELEMENT_COUNT)
        {

                LOG_EASUI_ERROR("FAILED TO ADD ELEMENT TO SCREEN : ELEMENT COUNT EXCEEDED THE MAXIMUM");


                return EASUI_ERROR;

        }


        SCREEN->ELEMENT_LIST[LAST_ELEMENT_INDEX + 1 - OFFSET] = ELEMENT;
        SCREEN->ELEMENT_LIST[LAST_ELEMENT_INDEX + 2 - OFFSET] = NULL;


        return EASUI_OK;

}


unsigned short GET_LAST_ELEMENT_INDEX(EASUI_SCREEN* SCREEN, int* OFFSET)
{

        *OFFSET = 0;


        if (SCREEN->ELEMENT_LIST[0] == NULL)
        {

                *OFFSET = 1;


                return 0;

        }


        unsigned short INDEX = 0;


        for (; SCREEN->ELEMENT_LIST[INDEX] != NULL; INDEX ++);


        return INDEX - 1;

}
