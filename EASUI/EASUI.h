#define EASUI
#ifdef EASUI



#include "MEMORY_ARENA/MEMORY_ARENA.h"
#include <stdio.h>
#include <stdlib.h>



#define EASUI_ERROR 0
#define EASUI_OK 1



enum TYPE_NUMBER
{

        EASUI_WINDOW_NUMBER,
        EASUI_TEXTBOX_NUMBER,
        EASUI_LABEL_NUMBER

};


void EASUI_INIT();
void EASUI_END();


int ADD__ELEMENT__TO__FRAMED_ELEMENT(void* FRAMED_ELEMENT, void* ELEMENT);


// ================================================== [WINDOW] =================================================

        typedef struct EASUI_WINDOW EASUI_WINDOW;


        struct EASUI_WINDOW
        {

                char TYPE;
                unsigned short MAX_ELEMENT_COUNT;
                void** ELEMENT_LIST;
                unsigned int WIDTH, HEIGHT;
                int (*ADD_ELEMENT)(EASUI_WINDOW* WINDOW, void* ELEMENT);

        };


        int SET_NEW_EASUI_WINDOW(EASUI_WINDOW* WINDOW, const unsigned short MAX_ELEMENT_COUNT, const unsigned int WIDTH, const unsigned int HEIGHT);

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


        int SET_NEW_EASUI_LABEL(EASUI_LABEL* LABEL, void* FRAMED_HOLDER, const unsigned int X_POSITION, const unsigned int Y_POSITION, const unsigned int WIDTH, const unsigned int HEIGHT, const unsigned int FONT_SIZE, const unsigned long MAX_STRING_SIZE);

// ===============================================================================================================



#endif
