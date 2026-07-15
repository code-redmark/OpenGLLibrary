#include "EASUI.h"



#define DEFAULT_PROGRAM_ARENA_SIZE 1024



void EASUI_INIT()
{

        INIT_MEMORY_AREMA(DEFAULT_PROGRAM_ARENA_SIZE);

}


void EASUI_END()
{

        FREE_MEMORY_ARENA();

}


int ADD__ELEMENT__TO__FRAMED_ELEMENT(void* FRAMED_ELEMENT, void* ELEMENT)
{

        char FRAMED_TYPE = *(char*)FRAMED_ELEMENT;


        if (FRAMED_TYPE == EASUI_WINDOW_NUMBER)
        {

                #define FRAMED_PTR ((EASUI_WINDOW*)FRAMED_ELEMENT)


                FRAMED_PTR->ADD_ELEMENT(FRAMED_PTR, ELEMENT);

        }
        else
        {

                return EASUI_ERROR;

        }


        return EASUI_OK;

}
