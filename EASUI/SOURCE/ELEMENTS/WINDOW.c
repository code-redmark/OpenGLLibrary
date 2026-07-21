#include "../../EASUI.h"




int WINDOW_ADD_ELEMENT(EASUI_WINDOW* WINDOW, void* ELEMENT);


int START(EASUI_WINDOW* WINDOW);


void UPDATE_SIZE_AND_CONTEXT_SIZE(EASUI_WINDOW* WINDOW);




int SET_NEW_EASUI_WINDOW(EASUI_WINDOW* WINDOW, const char* TITLE, const unsigned short MAX_ELEMENT_COUNT, const EASUIvec2 SIZE, const int RESIZABLE)
{

        // [CHECK FOR NULL POINTERS]
        {

                if (WINDOW == NULL || TITLE == NULL || (SIZE.x <= 0 || SIZE.y <= 0))
                {

                        LOG_EASUI_ERROR("FAILED TO SET NEW WINDOW : BAD_ARGUMENTS");


                        return EASUI_ERROR;

                }

        }


        // [SET BASE VALUES]
        {

                WINDOW->TYPE = EASUI_WINDOW_NUMBER;
                WINDOW->STATUS = EASUI_WINDOW_UNINITIALIZED;
                WINDOW->SIZE = SIZE;
                WINDOW->RESIZABLE = RESIZABLE;
                WINDOW->ACTIVE_SCREEN = &WINDOW->DEFAULT_SCREEN;
                WINDOW->ADD_ELEMENT = WINDOW_ADD_ELEMENT;
                WINDOW->START = START;
                WINDOW->UPDATE_SIZE_AND_CONTEXT_SIZE = UPDATE_SIZE_AND_CONTEXT_SIZE;
                WINDOW->BG_COLOR = (EASUIvec3){.x = 1.0f, .y = 1.0f, .z = 1.0f }; // white

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

        if (WINDOW->STATUS == EASUI_WINDOW_UNINITIALIZED)
        {

                LOG_EASUI_ERROR("FAILED TO START WINDOW : WINDOW WAS NOT INITIALIZED");


                return EASUI_ERROR;

        }


        // [CREATE WINDOW AND CONTEXT]
        {

                int SDL_WINDOW_FLAGS = SDL_WINDOW_OPENGL;


                // [SET SDL WINDOW FLAGS]
                {

                        if (WINDOW->RESIZABLE)
                        {

                                SDL_WINDOW_FLAGS |= SDL_WINDOW_RESIZABLE;

                        }

                }


                // [CREATE WINDOW]
                {

                        WINDOW->SDL_WINDOW = SDL_CreateWindow(WINDOW->TITLE, WINDOW->SIZE.x, WINDOW->SIZE.y, SDL_WINDOW_FLAGS);


                        if (!WINDOW->SDL_WINDOW)
                        {

                                LOG_EASUI_ERROR("FAILED TO START WINDOW : FAILED TO CREATE SDL WINDOW");


                                return EASUI_ERROR;

                        }

                }


                // [CREATE OPENGL CONTEXT IF NONE]
                {

                        if (EASUI__SDL_CONTEXT == EASUI_NONE)
                        {

                                EASUI__SDL_CONTEXT = SDL_GL_CreateContext(WINDOW->SDL_WINDOW);



                                if (!EASUI__SDL_CONTEXT)
                                {

                                        SDL_DestroyWindow(WINDOW->SDL_WINDOW);


                                        LOG_EASUI_ERROR("FAILED TO START WINDOW : FAILED TO CREATE SDL CONTEXT");


                                        return EASUI_ERROR;


                                }


                                // [LOAD GLAD]
                                {

                                        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
                                        {

                                                SDL_DestroyWindow(WINDOW->SDL_WINDOW);


                                                SDL_GL_DestroyContext(EASUI__SDL_CONTEXT);


                                                LOG_EASUI_ERROR("FAILED TO START WINDOW : FAILED TO LOAD GLAD");


                                                return EASUI_ERROR;

                                        }

                                }

                        }


                        SDL_GL_MakeCurrent(WINDOW->SDL_WINDOW, EASUI__SDL_CONTEXT);

                }


                SDL_GL_SetSwapInterval(1);


                SDL_GL_SwapWindow(WINDOW->SDL_WINDOW);


                WINDOW->STATUS = EASUI_WINDOW_RUNNNING;


                EASUI__RENDER_WINDOW(WINDOW);

        }


        return EASUI_OK;

}


int WINDOW_ADD_ELEMENT(EASUI_WINDOW* WINDOW, void* ELEMENT)
{

        if (WINDOW->STATUS == EASUI_NONE || WINDOW->STATUS == EASUI_WINDOW_UNINITIALIZED)
        {

                LOG_EASUI_ERROR("FAILED TO ADD ELEMENT TO WINDOW : WINDOW WAS NOT INITIALIZED");


                return EASUI_ERROR;

        }


        int ADD_ELEMENT_STATUS = (WINDOW->DEFAULT_SCREEN).ADD_ELEMENT(&WINDOW->DEFAULT_SCREEN, ELEMENT);


        if (ADD_ELEMENT_STATUS == EASUI_ERROR)
        {

                return EASUI_ERROR;

        }


        return EASUI_OK;

}


void UPDATE_SIZE_AND_CONTEXT_SIZE(EASUI_WINDOW* WINDOW)
{

        int NEW_WINDOW_WIDTH, NEW_WINDOW_HEIGHT;


        if (WINDOW == NULL)
        {

                LOG_EASUI_ERROR("FAILED TO UPDATE WINDOW CONTEXT SIZE : WINDOW IS NULL");


                return;

        }


        const int GET_WINDOW_SIZE_STATUS = SDL_GetWindowSizeInPixels(WINDOW->SDL_WINDOW, &NEW_WINDOW_WIDTH, &NEW_WINDOW_HEIGHT);


        if (!GET_WINDOW_SIZE_STATUS)
        {

                LOG_EASUI_ERROR("FAILED TO UPDATE WINDOW CONTEXT SIZE : SDL FAILED TO GET WINDOW SIZE");


                return;

        }


        WINDOW->SIZE.x = NEW_WINDOW_WIDTH;
        WINDOW->SIZE.y = NEW_WINDOW_HEIGHT;


        glViewport(0, 0, NEW_WINDOW_WIDTH, NEW_WINDOW_HEIGHT);

}
