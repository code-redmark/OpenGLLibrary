#define EASUI
#ifdef EASUI

#include <stdio.h>
#include <stdlib.h>


#define EASUI_ERROR 0
#define EASUI_OK 1



enum TYPE_NUMBER
{

        EASUI_TEXTBOX_NUMBER,
        EASUI_LABEL_NUMBER

};


// ================================================== [WINDOW] =================================================

        typedef struct EASUI_WINDOW EASUI_WINDOW;

// =============================================================================================================


// =================================================== [LABEL] =================================================

        typedef struct EASUI_LABEL EASUI_LABEL;

        struct EASUI_LABEL
        {

                char TYPE;
                unsigned long MAX_STRING_SIZE;
                unsigned int X_POSITION, Y_POSITION, WIDTH, HEIGHT, FONT_SIZE;
                char* TEXT;
                void (*TEST_FUNCTION)(const EASUI_LABEL* LABEL);

        };

        int SET_NEW_EASUI_LABEL(EASUI_LABEL* LABEL, const unsigned int X_POSITION, const unsigned int Y_POSITION, const unsigned int WIDTH, const unsigned int HEIGHT, const unsigned int FONT_SIZE, const unsigned long MAX_STRING_SIZE);

// ===============================================================================================================



#endif
