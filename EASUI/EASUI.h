#define EASUI
#ifdef EASUI


#include "MEMORY_ARENA/MEMORY_ARENA.h"
#include <stdio.h>
#include <stdlib.h>

#include "../EASUI/DEPENDENCIES/COMMON/STRINGS.h"

#define EASUI_ERROR 0
#define EASUI_OK 1

#define MAX_STRING_LENGTH = 4294967296;
#define MAX_FONT_SIZE = 65536;

// Not setting this up yet
//#define MAX_CONTAINER_CHILDREN_AMOUNT = 4294967296;

typedef enum ELEMENT_TYPE ELEMENT_TYPE;

enum ELEMENT_TYPE
{
        E_EASUI_WINDOW,
        E_EASUI_SCREEN,
        E_EASUI_TEXTBOX,
        E_EASUI_LABEL,

        ELEMENT_TYPE_COUNT
};

void EASUI_INIT();
void EASUI_END();


typedef struct EASUIvec2 EASUIvec2;

struct EASUIvec2 {
    uint16_t x;
    uint16_t y;
};

typedef struct EASUI_ELEMENT EASUI_ELEMENT;

struct EASUI_ELEMENT {
    ELEMENT_TYPE TYPE;
};


typedef struct EASUI_CONTAINER EASUI_CONTAINER;

struct EASUI_CONTAINER {
    ELEMENT_TYPE TYPE;

    EASUI_ELEMENT** CHILDREN_LIST;
    uint16_t MAX_ELEMENT_COUNT;
    int (*ADD_ELEMENT)(EASUI_CONTAINER* CONTAINER_ELEMENT, EASUI_ELEMENT* ELEMENT);
    int (*LAST_ELEMENT_INDEX)(EASUI_ELEMENT);
};

int CONTAINER_ADD_ELEMENT(EASUI_CONTAINER* CONTAINER_ELEMENT, EASUI_ELEMENT* ELEMENT);
int CONTAINER_LAST_ELEMENT_INDEX(EASUI_CONTAINER* CONTAINER);


// =================================================== [SCREEN] =================================================

typedef struct EASUI_SCREEN EASUI_SCREEN;

struct EASUI_SCREEN
{
    ELEMENT_TYPE TYPE;
    EASUI_ELEMENT** CHILDREN_LIST;
    uint16_t MAX_ELEMENT_COUNT;
    int (*ADD_ELEMENT)(EASUI_CONTAINER* CONTAINER_ELEMENT, EASUI_ELEMENT* ELEMENT);
    int (*LAST_ELEMENT_INDEX)(EASUI_CONTAINER* CONTAINER);

};

int SET_NEW_EASUI_SCREEN(EASUI_SCREEN* SCREEN, uint16_t MAX_ELEMENT_COUNT);

// ===============================================================================================================

// ================================================== [WINDOW] =================================================

        typedef struct EASUI_WINDOW EASUI_WINDOW;

        /*
        
            Acts as both as the way to setup the OpenGL
            Context to run our program and as a basic container

        */
        struct EASUI_WINDOW
        {

                ELEMENT_TYPE TYPE;

                /*
                    The window's default children list,

                    this is used when CURRENT_SCREEN is set to NULL and is useful
                    for who just wants to have a small one-screen program,
                    
                    if this is set to NULL the renderer will render a black window
                */
                EASUI_ELEMENT** CHILDREN_LIST;

                uint16_t MAX_ELEMENT_COUNT;

                int (*ADD_ELEMENT)(EASUI_CONTAINER* CONTAINER_ELEMENT, EASUI_ELEMENT* ELEMENT);
                int (*LAST_ELEMENT_INDEX)(EASUI_CONTAINER* CONTAINER);


                /*
                    The size of the window in pixels
                */
                EASUIvec2 SIZE;


                /*
                    The EASUI_SCREEN to be rendered on this window.

                    If set to NULL, the Renderer will ignore this and render
                    the window's default CHILDREN_LIST property
                */
                EASUI_SCREEN* CURRENT_SCREEN;

                /*
                    Sets the Window's CURRENT_SCREEN property, if set to NULL
                    the renderer will start rendering using the default children list.
                */
                int (*SET_SCREEN)(EASUI_WINDOW* WINDOW, EASUI_SCREEN* SCREEN);

        };


        int SET_NEW_EASUI_WINDOW(EASUI_WINDOW* WINDOW, uint16_t MAX_ELEMENT_COUNT, EASUIvec2 SIZE);
        int SET_WINDOW_SCREEN(EASUI_WINDOW* WINDOW, EASUI_SCREEN* SCREEN);

// =============================================================================================================

// =================================================== [LABEL] =================================================

        typedef struct EASUI_LABEL EASUI_LABEL;


        struct EASUI_LABEL
        {
                ELEMENT_TYPE TYPE;
                uint32_t MAX_STRING_SIZE;
                EASUIvec2 POSITION, SIZE;
                char* TEXT;
                uint8_t FONT_SIZE;
                void (*PRINT)(const EASUI_LABEL* LABEL);
                int (*SET_TEXT)(EASUI_LABEL* LABEL, const char* TEXT);
        };

        int SET_NEW_EASUI_LABEL(EASUI_LABEL* LABEL, EASUI_CONTAINER* PARENT, const EASUIvec2 POSITION, const EASUIvec2 SIZE, const uint8_t FONT_SIZE);
        int SET_LABEL_TEXT(EASUI_LABEL* LABEL, const char* TEXT);

// ===============================================================================================================





#endif
