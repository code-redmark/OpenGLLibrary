#include "../../EASUI.h"




int WINDOW_ADD_ELEMENT(EASUI_WINDOW* WINDOW, void* ELEMENT);


int START(EASUI_WINDOW* WINDOW);




int SET_NEW_EASUI_WINDOW(EASUI_WINDOW* WINDOW, const char* TITLE, const unsigned short MAX_ELEMENT_COUNT, const unsigned int WIDTH, const unsigned int HEIGHT)
{

        // [CHECK FOR NULL POINTERS]
        {

                if (WINDOW == NULL || TITLE == NULL)
                {

                        LOG_EASUI_ERROR("FAILED TO SET NEW WINDOW : BAD_ARGUMENTS");


                        return EASUI_ERROR;

                }

        }


        // [SET BASE VALUES]
        {

                WINDOW->TYPE = EASUI_WINDOW_NUMBER;
                WINDOW->STATUS = EASUI_WINDOW_UNINITIALIZED;
                WINDOW->WIDTH = WIDTH;
                WINDOW->HEIGHT = HEIGHT;
                WINDOW->ACTIVE_SCREEN = &WINDOW->DEFAULT_SCREEN;
                WINDOW->ADD_ELEMENT = WINDOW_ADD_ELEMENT;
                WINDOW->START = START;

        }


        // [ALLOCATE MEMORY FOR DEFAULT SCREEN ELEMENT LIST]
        {

                const int SET_DEFAULT_SCREEN_STATUS = SET_NEW_EASUI_SCREEN(&WINDOW->DEFAULT_SCREEN, MAX_ELEMENT_COUNT);


                if (SET_DEFAULT_SCREEN_STATUS == EASUI_ERROR)
                {

                        return EASUI_ERROR;

                }

        }


        //  [ALLOCATE MEMORY FOR TITLE]
        {

                const unsigned long TITLE_SIZE = STRING_SIZE(TITLE);


                WINDOW->TITLE = MEMORY_ARENA_ALLOC(TITLE_SIZE);


                if (WINDOW->TITLE == NULL)
                {

                        LOG_EASUI_ERROR("FAILED TO SET NEW WINDOW : FAILED TO ALLOCATED MEMORY FOR WINDOW TITLE");


                        return EASUI_ERROR;

                }


                STRING_COPY(WINDOW->TITLE, TITLE);

        }


        WINDOW->STATUS = EASUI_WINDOW_READY;


        // [ADD WINDOW TO WINDOW LIST]
        {

                int ADD_WINDOW_STATUS = EASUI__ADD_WINDOW_TO_WINDOW_LIST(WINDOW);


                if (ADD_WINDOW_STATUS == EASUI_ERROR)
                {

                        WINDOW->STATUS = EASUI_WINDOW_UNINITIALIZED;


                        return EASUI_ERROR;

                }

        }


        return EASUI_OK;

}


int START(EASUI_WINDOW* WINDOW)
{

        // [CREATE WINDOW AND CONTEXT]
        {

                WINDOW->SDL_WINDOW = SDL_CreateWindow(WINDOW->TITLE, WINDOW->WIDTH, WINDOW->HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);


                if (!WINDOW->SDL_WINDOW)
                {

                        LOG_EASUI_ERROR("FAILED TO START WINDOW : FAILED TO CREATE SDL WINDOW");


                        return EASUI_ERROR;

                }


                WINDOW->SDL_CONTEXT = SDL_GL_CreateContext(WINDOW->SDL_WINDOW);


                if (!WINDOW->SDL_CONTEXT)
                {

                        SDL_DestroyWindow(WINDOW->SDL_WINDOW);


                        LOG_EASUI_ERROR("FAILED TO START WINDOW : FAILED TO CREATE SDL CONTEXT");


                        return EASUI_ERROR;
                }


                SDL_GL_MakeCurrent(WINDOW->SDL_WINDOW, WINDOW->SDL_CONTEXT);


                SDL_GL_SetSwapInterval(1);


                WINDOW->STATUS = EASUI_WINDOW_RUNNNING;

        }


        return EASUI_OK;

}


int WINDOW_ADD_ELEMENT(EASUI_WINDOW* WINDOW, void* ELEMENT)
{

        int ADD_ELEMENT_STATUS = (WINDOW->DEFAULT_SCREEN).ADD_ELEMENT(&WINDOW->DEFAULT_SCREEN, ELEMENT);


        if (ADD_ELEMENT_STATUS == EASUI_ERROR)
        {

                return EASUI_ERROR;

        }


        return EASUI_OK;

}
