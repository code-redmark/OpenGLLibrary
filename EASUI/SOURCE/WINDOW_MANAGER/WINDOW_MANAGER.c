#include "../../EASUI.h"
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <time.h>



EASUI_WINDOW** WINDOW_LIST;
EASUI_WINDOW* ACTIVE_WINDOW;


unsigned short LAST_WINDOW_INDEX;
unsigned short MAX_WINDOW_COUNT;
unsigned short FRAMETIME_MILISECONDS;


pthread_t WINDOW_MANAGER_MAIN__THREAD;



void* WINDOW_MANAGER_MAIN(void* ARG);


EASUI_WINDOW* GET__WINDOW__FROM__SDL_WINDOW(const SDL_Window* SDL_WINDOW);


EASUI_WINDOW* GET_FOCUSED_WINDOW();


int NO_WINDOWS_RUNNING();


int SET_FRAMETIME();




int EASUI__SETUP_WINDOW_LIST(const unsigned short WINDOW_COUNT)
{

        if (WINDOW_COUNT == 0)
        {

                LOG_EASUI_CRITICAL_ERROR("FAILED TO SETUP WINDOW LIST : WINDOW COUNT MUST BE ATLEAST 1");


                EASUI_WAIT_AND_END();


                return EASUI_ERROR;

        }


        MAX_WINDOW_COUNT = WINDOW_COUNT;


        LAST_WINDOW_INDEX = 0;


        WINDOW_LIST = MEMORY_ARENA_ALLOC(sizeof(EASUI_WINDOW*) * WINDOW_COUNT);


        if (WINDOW_LIST == NULL)
        {

                LOG_EASUI_CRITICAL_ERROR("FAILED TO SETUP WINDOW LIST : FAILED TO ALLOCATE MEMORY FOR WINDOW LIST");


                return EASUI_ERROR;

        }


        WINDOW_LIST[0] = NULL;


        return EASUI_OK;

}


int EASUI__WINDOW_MANAGER_START()
{

        // [SET FRAMETIME]
        {

                int SET_FRAMETIME_STATUS = SET_FRAMETIME();


                if (SET_FRAMETIME_STATUS == EASUI_ERROR)
                {

                        return EASUI_ERROR;

                }

        }


        // [START MAIN THREAD]
        {

                const int CREATE_THREAD_STATUS = pthread_create(&WINDOW_MANAGER_MAIN__THREAD, NULL, WINDOW_MANAGER_MAIN, NULL);


                if (CREATE_THREAD_STATUS != 0)
                {

                        LOG_EASUI_ERROR("FAILED TO START WINDOW MANAGER : FAILED TO CREATE WINDOW MANAGER MAIN THREAD");


                        return EASUI_ERROR;

                }

        }


        return EASUI_OK;

}


int EASUI__WINDOW_MANAGER_WAIT_AND_END()
{

        if (pthread_join(WINDOW_MANAGER_MAIN__THREAD, NULL) != 0)
        {

                LOG_EASUI_CRITICAL_ERROR("FAILED TO WAIT AND END WINDOW MANAGER : FAILED TO JOIN WINDOW MANAGER MAIN THREAD");


                return EASUI_ERROR;

        }


        return EASUI_OK;

}


void* WINDOW_MANAGER_MAIN(void* ARG)
{

        // [WAIT FOR A WINDOW TO BE RUNNING]
        {

                while (WINDOW_LIST[0] == NULL);


                while (NO_WINDOWS_RUNNING());

        }


        while (!NO_WINDOWS_RUNNING())
        {

                int WINDOW_EVENT = EASUI__POLL_EVENTS();


                EASUI_WINDOW* CURRENT_WINDOW = GET_FOCUSED_WINDOW();


                if (CURRENT_WINDOW == NULL)
                {

                        continue;

                }


                if (WINDOW_EVENT == EASUI_CLOSE_WINDOW_EVENT)
                {

                        SDL_GL_DestroyContext(CURRENT_WINDOW->SDL_CONTEXT);


                        SDL_DestroyWindow(CURRENT_WINDOW->SDL_WINDOW);


                        CURRENT_WINDOW->STATUS = EASUI_WINDOW_CLOSED;

                }


                // ==============! TEMPORARY !==============
                for (unsigned short INDEX = 0; INDEX <= LAST_WINDOW_INDEX; INDEX++)
                {

                        EASUI_WINDOW* CURRENT_WINDOW = WINDOW_LIST[INDEX];


                        if (CURRENT_WINDOW->STATUS == EASUI_WINDOW_RUNNNING)
                        {

                                CURRENT_WINDOW->UPDATE_CONTEXT_SIZE(CURRENT_WINDOW);


                                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                                glClear(GL_COLOR_BUFFER_BIT);


                                SDL_GL_SwapWindow(CURRENT_WINDOW->SDL_WINDOW);

                        }

                }


                SDL_Delay(FRAMETIME_MILISECONDS);

        }


        return NULL;

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

                const int OFFSET = (WINDOW_LIST[0] == NULL);


                if (LAST_WINDOW_INDEX + 1 - OFFSET >= MAX_WINDOW_COUNT)
                {

                        LOG_EASUI_ERROR("FAILED TO ADD WINDOW TO WINDOW LIST : NUMBER OF WINDOWS HAS EXCEEDED THE MAXIMUM");


                        return EASUI_ERROR;

                }


                WINDOW_LIST[LAST_WINDOW_INDEX + 1 - OFFSET] = WINDOW;


                if (!OFFSET)
                {

                        LAST_WINDOW_INDEX ++;

                }


                ACTIVE_WINDOW = WINDOW;

        }


        return EASUI_OK;

}


int NO_WINDOWS_RUNNING()
{

        for (unsigned short INDEX = 0; INDEX <= LAST_WINDOW_INDEX; INDEX ++)
        {

                if (WINDOW_LIST[INDEX]->STATUS == EASUI_WINDOW_RUNNNING)
                {

                        return FALSE;

                }

        }


        return TRUE;

}


EASUI_WINDOW* GET_FOCUSED_WINDOW()
{

        const SDL_Window* FOCUSED_SDL_WINDOW = SDL_GetKeyboardFocus();



        if (FOCUSED_SDL_WINDOW == NULL)
        {

                return NULL;

        }


        for (unsigned short INDEX = 0; INDEX <= LAST_WINDOW_INDEX; INDEX ++)
        {

                if (WINDOW_LIST[INDEX]->SDL_WINDOW == FOCUSED_SDL_WINDOW)
                {

                        return WINDOW_LIST[INDEX];

                }

        }


        LOG_EASUI_ERROR("COULDNT GET FOCUSED WINDOW : COULDNT MATCH FOCUSED SDL WINDOW WITHIN WINDOW LIST");


        return NULL;

}


EASUI_WINDOW* GET__WINDOW__FROM__SDL_WINDOW(const SDL_Window* SDL_WINDOW)
{

        if (SDL_WINDOW == NULL)
        {

                LOG_EASUI_ERROR("COULDNT GET WINDOW FROM SDL WINDOW : SDL WINDOW IS NULL");


                return NULL;

        }


        for (unsigned short INDEX = 0; INDEX <= LAST_WINDOW_INDEX; INDEX ++)
        {

                if (WINDOW_LIST[INDEX]->SDL_WINDOW == SDL_WINDOW)
                {

                        return WINDOW_LIST[INDEX];

                }

        }


        LOG_EASUI_ERROR("COULDNT GET WINDOW FROM SDL WINDOW : NO WINDOW HAS THE SDL WINDOW");


        return NULL;

}


int SET_FRAMETIME()
{

        const SDL_DisplayMode* DISPLAY_MODE;


        // [GET DISPLAY MODE]
        {

                SDL_DisplayID DISPLAY_ID = SDL_GetPrimaryDisplay();


                if (DISPLAY_ID == 0)
                {

                        LOG_EASUI_ERROR("FAILED TO SET FRAMETIME : DISPLAY ID IS 0");


                        return EASUI_ERROR;
                }


                DISPLAY_MODE = SDL_GetDesktopDisplayMode(DISPLAY_ID);


                if (!DISPLAY_MODE)
                {

                        LOG_EASUI_ERROR("FAILED TO SET FRAMETIME : DISPLAY MODE IS NULL");


                        return EASUI_ERROR;

                }

        }


        FRAMETIME_MILISECONDS = 1000 / DISPLAY_MODE->refresh_rate;


        return EASUI_OK;

}
