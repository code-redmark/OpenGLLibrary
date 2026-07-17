#define EASUI
#ifdef EASUI


#include "SOURCE/MEMORY_ARENA/MEMORY_ARENA.h"
#include "DEPENDENCIES/COMMON/STRINGS.h"
#include "DEPENDENCIES/GLAD/include/glad/glad.h"
#include <pthread.h>
#include <SDL3/SDL.h>


#define EASUI_ERROR 0
#define EASUI_OK 1



enum EASUI_ELEMENT_TYPE_NUMBERS
{

        EASUI_WINDOW_NUMBER,
        EASUI_SCREEN_NUMBER,
        EASUI_TEXTBOX_NUMBER,
        EASUI_LABEL_NUMBER

};

enum EASUI_WINDOW_STATUS_NUMBERS
{

        EASUI_WINDOW_UNINITIALIZED,
        EASUI_WINDOW_READY,
        EASUI_WINDOW_RUNNNING,
        EASUI_WINDOW_CLOSED,

};


typedef struct EASUI_SCREEN EASUI_SCREEN;
typedef struct EASUI_WINDOW EASUI_WINDOW;


// ================================================== [FUNCTIONS] =================================================
//

int EASUI_INIT(const unsigned short MAX_WINDOW_COUNT);


void EASUI_END();


int EASUI__SETUP_WINDOW_LIST(const unsigned short MAX_WINDOW_COUNT);


int EASUI__ADD_WINDOW_TO_WINDOW_LIST(EASUI_WINDOW* WINDOW);


int EASUI__WINDOW_MANAGER_START();


int ADD__ELEMENT__TO__FRAMED_ELEMENT(void* FRAMED_ELEMENT, void* ELEMENT);


void LOG_EASUI_ERROR(const char* MESSAGE);

//
// ================================================================================================================



// ================================================== [SCREEN] =================================================
//

        struct EASUI_SCREEN
        {

                char TYPE;
                void** ELEMENT_LIST;
                unsigned short LAST_ELEMENT_INDEX;
                unsigned short MAX_ELEMENT_COUNT;
                int (*ADD_ELEMENT)(EASUI_SCREEN* SCREEN, void* ELEMENT);

        };


        int SET_NEW_EASUI_SCREEN(EASUI_SCREEN* SCREEN, const unsigned short MAX_ELEMENT_COUNT);

//
// =============================================================================================================


// ================================================== [WINDOW] =================================================

        struct EASUI_WINDOW
        {

                char TYPE;
                char STATUS;
                SDL_Window* SDL_WINDOW;
                SDL_GLContext SDL_CONTEXT;
                EASUI_SCREEN* ACTIVE_SCREEN;
                EASUI_SCREEN DEFAULT_SCREEN;
                unsigned int WIDTH, HEIGHT;
                int (*ADD_ELEMENT)(EASUI_WINDOW* WINDOW, void* ELEMENT);
                int (*START)(EASUI_WINDOW* WINDOW);
                char* TITLE;

        };


        int SET_NEW_EASUI_WINDOW(EASUI_WINDOW* WINDOW, const char* TITLE, const unsigned short MAX_ELEMENT_COUNT, const unsigned int WIDTH, const unsigned int HEIGHT);

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
