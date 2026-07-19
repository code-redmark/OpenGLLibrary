#include "../EASUI.h"





int EASUI__INIT(const unsigned short MAX_WINDOW_COUNT)
{

        // [SETUP SDL]
        {

                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
                SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
                SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


                #ifdef __linux__

                        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, getenv("XDG_SESSION_TYPE"));

                #endif


                if (!SDL_Init(SDL_INIT_VIDEO))
                {

                        LOG_EASUI_CRITICAL_ERROR("FAILED TO INITIALIZE SDL VIDIEO");


                        return EASUI_ERROR;

                }

        }


        INIT_MEMORY_ARENA(1024);


        EASUI__WINDOW_MANAGER__INIT(MAX_WINDOW_COUNT);


        return EASUI_OK;

}


int EASUI__RUN()
{

        int WINDOW_MANAGER_RUN_STATUS = EASUI__WINDOW_MANAGER__RUN();


        // [END EASUI]
        {

                SDL_Quit();


                FREE_MEMORY_ARENA();

        }


        if (WINDOW_MANAGER_RUN_STATUS == EASUI_OK)
        {

                return EASUI_ERROR;

        }


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


void LOG_EASUI_ERROR(const char* MESSAGE)
{

        fprintf(stderr, "\033[1;31m[EASUI ERROR]\033[0m : | %s |\n", MESSAGE);

}


void LOG_EASUI_CRITICAL_ERROR(const char* MESSAGE)
{

        fprintf(stderr, "\033[1;31m[EASUI *CRITICAL* ERROR]\033[0m : | %s |\n", MESSAGE);

}
