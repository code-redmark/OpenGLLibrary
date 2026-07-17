#include "../../EASUI.h"




int SCREEN_ADD_ELEMENT(EASUI_SCREEN* SCREEN, void* ELEMENT);




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
                SCREEN->LAST_ELEMENT_INDEX = 0;
                SCREEN->ADD_ELEMENT = SCREEN_ADD_ELEMENT;

        }


        // [ALLOCATE MEMORY FOR ELEMENT LIST]
        {

                SCREEN->ELEMENT_LIST = MEMORY_ARENA_ALLOC(sizeof(void*) * MAX_ELEMENT_COUNT);


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

        if (SCREEN->LAST_ELEMENT_INDEX + 1 >= SCREEN->MAX_ELEMENT_COUNT)
        {

                LOG_EASUI_ERROR("FAILED TO ADD ELEMENT TO SCREEN : ELEMENT COUNT EXCEEDED THE MAXIMUM");


                return EASUI_ERROR;

        }


        const int OFFSET = (SCREEN->ELEMENT_LIST[0] == NULL);


        SCREEN->ELEMENT_LIST[SCREEN->LAST_ELEMENT_INDEX + 1 - OFFSET] = ELEMENT;


        return EASUI_OK;

}
