#include "../../EASUI.h"




int EASUI__GET_EVENTS()
{

        SDL_Event SDL_EVENT;


        while (SDL_PollEvent(&SDL_EVENT) != 0)
        {

                if (SDL_EVENT.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
                {

                        return EASUI_CLOSE_WINDOW_EVENT;

                }

        }


        SDL_Delay(FRAMETIME_MILLISECONDS);


        return EASUI_NO_WINDOW_EVENT;

}
