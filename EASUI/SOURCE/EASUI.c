#include "../EASUI.h"
#include <SDL3/SDL_init.h>



void LOG_EASUI_ERROR(const char* MESSAGE)
{

        fprintf(stderr, "[EASUI ERROR] : | %s | [LINE] : %d\n ", MESSAGE, __LINE__);

}


int EASUI_INIT(const unsigned short MAX_WINDOW_COUNT)
{

        INIT_MEMORY_AREMA(1024);


        EASUI__SETUP_WINDOW_LIST(MAX_WINDOW_COUNT);


        // !-- TODO : FIX POLL EVENTS NOT WORKING ISSUE --!
        if (!SDL_Init(SDL_INIT_VIDEO))
        {

                LOG_EASUI_ERROR("FAILED TO INITIALIZE SDL VIDIEO");


                return EASUI_ERROR;

        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


        EASUI__WINDOW_MANAGER_START();


        return EASUI_OK;

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


int EASUI_WAIT_AND_END()
{

        EASUI__WINDOW_MANAGER_WAIT_AND_END();


        FREE_MEMORY_ARENA();


        SDL_Quit();


        return EASUI_OK;

}
