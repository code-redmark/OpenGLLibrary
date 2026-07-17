#include "EASUI/EASUI.h"
#include <stdio.h>



int main()
{

    EASUI_WINDOW testWindow;
    SET_NEW_EASUI_WINDOW(&testWindow, 67, (EASUIvec2){ .x = 640, .y = 480 });

    EASUI_LABEL testLabel1;
    SET_NEW_EASUI_LABEL(&testLabel1, (EASUI_CONTAINER*)(&testWindow), (EASUIvec2) { .x = 0, .y = 0 }, (EASUIvec2) { .x = 200, .y = 100 }, 16);

    EASUI_LABEL testLabel2;
    SET_NEW_EASUI_LABEL(&testLabel2, (EASUI_CONTAINER*)(&testWindow), (EASUIvec2) { .x = 0, .y = 0 }, (EASUIvec2) { .x = 200, .y = 100 }, 16);

    EASUI_WINDOW testWindow2;
    SET_NEW_EASUI_WINDOW(&testWindow2, 67, (EASUIvec2) { .x = 640, .y = 480 });

    EASUI_SCREEN testScreen;
    SET_NEW_EASUI_SCREEN(&testScreen, 67);

    testWindow.SET_SCREEN(&testWindow, &testScreen);

    EASUI_INIT();


    // [RUN PART]
    {

        testLabel1.SET_TEXT(&testLabel1, "Hello");
        testLabel1.PRINT(&testLabel1);
        testLabel2.SET_TEXT(&testLabel2, "World");
        testLabel2.PRINT(&testLabel2);

        printf("\n\nscreen address: %p \nFrom window: %p\n\n", &testScreen, &testWindow.CURRENT_SCREEN);

    }


    EASUI_END();



    return 0;

}
