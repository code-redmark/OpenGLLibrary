#include "../../EASUI.h"



EASUI_WINDOW** WINDOW_LIST;
EASUI_WINDOW* ACTIVE_WINDOW;


unsigned long MAX_WINDOW_COUNT;


unsigned short GET_LAST_WINDOW_INDEX(int* OFFSET);



int EASUI__SETUP_WINDOW_LIST(const unsigned short WINDOW_COUNT)
{

        MAX_WINDOW_COUNT = WINDOW_COUNT;


        WINDOW_LIST = MEMORY_ARENA_ALLOC(sizeof(EASUI_WINDOW*) * (WINDOW_COUNT + 1));


        if (WINDOW_LIST == NULL)
        {

                LOG_EASUI_ERROR("FAILED TO SETUP WINDOW LIST : FAILED TO ALLOCATE MEMORY FOR WINDOW LIST");


                return EASUI_ERROR;

        }


        WINDOW_LIST[0] = NULL;


        return EASUI_OK;

}


int EASUI__WINDOW_MANAGER_START()
{

        // [WAIT FOR A WINDOW TO BE RUNNING]
        {

                while (1)
                {

                        int IS_EMPTY;

                        GET_LAST_WINDOW_INDEX(&IS_EMPTY);


                        if (!IS_EMPTY)
                        {

                                break;

                        }

                }


                while (WINDOW_LIST[0]->STATUS != EASUI_WINDOW_RUNNNING);

        }


        // ----------------------------------
        // -- [ TODO : PLUG INPUT EVENTS ] --
        // ----------------------------------


        return EASUI_OK;

}

int EASUI__ADD_WINDOW_TO_WINDOW_LIST(EASUI_WINDOW* WINDOW)
{

        if (WINDOW == NULL)
        {

                LOG_EASUI_ERROR("FAILED TO ADD WINDOW TO WINDOW LIST : ADDED WINDOW IS NULL");


                return EASUI_ERROR;

        }


        // [ADD WINDOW TO WINDOW LIST]
        {

                int OFFSET;

                const int LAST_INDEX = GET_LAST_WINDOW_INDEX(&OFFSET);


                if (LAST_INDEX + 1 == MAX_WINDOW_COUNT)
                {

                        LOG_EASUI_ERROR("FAILED TO ADD WINDOW TO WINDOW LIST : NUMBER OF WINDOWS HAS EXCEEDED THE MAXIMUM");


                        return EASUI_ERROR;

                }


                WINDOW_LIST[LAST_INDEX + 1 - OFFSET] = WINDOW;
                WINDOW_LIST[LAST_INDEX + 2 - OFFSET] = NULL;


                ACTIVE_WINDOW = WINDOW;

        }


        return EASUI_OK;

}


unsigned short GET_LAST_WINDOW_INDEX(int* OFFSET)
{

        *OFFSET = FALSE;


        if (WINDOW_LIST[0] == NULL)
        {

                *OFFSET = TRUE;


                return 0;

        }


        unsigned short INDEX = 0;


        for (; WINDOW_LIST[INDEX] != NULL; INDEX ++);


        return INDEX;

}
