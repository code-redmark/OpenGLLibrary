// #include <SDL3/SDL.h>
// #include "../../EASUI/DEPENDENCIES/GLAD/include/glad/glad.h"
// #include <stdio.h>

// int main() {
//     if (!SDL_Init(SDL_INIT_VIDEO)) {
//         printf("SDL_Init error: %s\n", SDL_GetError());
//         return 1;
//     }

//     SDL_Window* win = SDL_CreateWindow("Test", 800, 600, SDL_WINDOW_OPENGL);
//     if (!win) {
//         printf("SDL_CreateWindow error: %s\n", SDL_GetError());
//         return 1;
//     }

//     SDL_GLContext gl_context = SDL_GL_CreateContext(win);

//     // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//     // glClear(GL_COLOR_BUFFER_BIT);

//     // 3. Force Wayland to register the frame
//     SDL_GL_SwapWindow(win);


//     //SDL_ShowWindow(win);
//     SDL_Delay(6000);
//     SDL_DestroyWindow(win);
//     SDL_Quit();

//     return 0;
// }


#include "../../EASUI/EASUI.h"
#include <stdio.h>

int main()
{

        EASUI_WINDOW TEST_WINDOW, TEST_WINDOW_2;
        EASUI_LABEL TEST_LABEL;
        EASUI_LABEL TEST_LABEL_2;


        EASUI_INIT(3);


        // [RUN PART]
        {

                SET_NEW_EASUI_WINDOW(&TEST_WINDOW, "HELLO", 16, 600, 200);
                SET_NEW_EASUI_WINDOW(&TEST_WINDOW_2, "HELLO_2", 16, 300, 200);


                printf("ADDRESS OF WINDOW ELEMENT_LIST = %p\n\n", TEST_WINDOW.DEFAULT_SCREEN.ELEMENT_LIST);


                SET_NEW_EASUI_LABEL(&TEST_LABEL, &TEST_WINDOW, 0, 0, 20, 10, 12, 1024);
                SET_NEW_EASUI_LABEL(&TEST_LABEL_2, &TEST_WINDOW, 0, 0, 20, 10, 12, 1024);


                printf("ADDRESS OF TEST_LABEL = %p\n", &TEST_LABEL);
                printf("ADDRESS OF WINDOW ELEMENT_LIST[0] (SHOULD BE TEST_LABEL) = %p\n\n", (void*)TEST_WINDOW.DEFAULT_SCREEN.ELEMENT_LIST[0]);

                printf("ADDRESS OF TEST_LABEL_2 = %p\n", &TEST_LABEL_2);
                printf("ADDRESS OF WINDOW ELEMENT_LIST[1] (SHOULD BE TEST_LABEL_2) = %p\n", TEST_WINDOW.DEFAULT_SCREEN.ELEMENT_LIST[1]);


                TEST_WINDOW.START(&TEST_WINDOW);
                TEST_WINDOW_2.START(&TEST_WINDOW_2);

        }


        EASUI_WAIT_AND_END();



        return 0;

}
