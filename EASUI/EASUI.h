#define EASUI
#ifdef EASUI


#include "SOURCE/MEMORY_ARENA/MEMORY_ARENA_PRIVATE.h"

#include "DEPENDENCIES/GLAD/include/glad/glad.h"
#include "DEPENDENCIES/COMMON/STRINGS.h"
#include <SDL3/SDL.h>
#include <stdio.h>


#define EASUI__DEFAULT__REFRESH_RATE 60
#define EASUI__DEFAULT__MEMORY_ARENA_SIZE 1024


#define EASUI_NONE 0
#define EASUI_ERROR 0
#define EASUI_OK 1



enum EASUI_ELEMENT_TYPE_NUMBERS
{

        EASUI_WINDOW_NUMBER,
        EASUI_SCREEN_NUMBER,
        EASUI_TEXTBOX_NUMBER,
        EASUI_LABEL_NUMBER,
        EASUI_FRAME_NUMBER

};

enum EASUI_WINDOW_STATUS_NUMBERS
{

        EASUI_WINDOW_UNINITIALIZED,
        EASUI_WINDOW_READY,
        EASUI_WINDOW_RUNNNING,
        EASUI_WINDOW_CLOSED,

};

enum EASUI_WINDOW_EVENT_NUMBERS
{

        EASUI_NO_WINDOW_EVENT,
        EASUI_CLOSE_WINDOW_EVENT,

};


typedef struct EASUI_SCREEN EASUI_SCREEN;
typedef struct EASUI_WINDOW EASUI_WINDOW;


extern SDL_GLContext EASUI__SDL_CONTEXT;
extern unsigned short FRAMETIME_MILLISECONDS;

typedef struct EASUIvec3 EASUIvec3;

struct EASUIvec3 {
        float x;
        float y;
        float z;
};

typedef struct EASUIvec2 EASUIvec2;

struct EASUIvec2 {
        float x;
        float y;
};

// ================================================== [FUNCTIONS] =================================================
//

int EASUI__INIT(const unsigned short MAX_WINDOW_COUNT);


int EASUI__RUN();


int EASUI__WINDOW_MANAGER__INIT(const unsigned short MAX_WINDOW_COUNT);


int EASUI__WINDOW_MANAGER__RUN();


int EASUI__ADD_WINDOW_TO_WINDOW_LIST(EASUI_WINDOW* WINDOW);


EASUI_WINDOW* GET_FOCUSED_WINDOW();


int EASUI__RENDER_WINDOW(EASUI_WINDOW* WINDOW);


int EASUI__GET_EVENTS();


int ADD__ELEMENT__TO__FRAMED_ELEMENT(void* FRAMED_ELEMENT, void* ELEMENT);


void LOG_EASUI_ERROR(const char* MESSAGE);


void LOG_EASUI_CRITICAL_ERROR(const char* MESSAGE);

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
                EASUI_SCREEN* ACTIVE_SCREEN;
                EASUI_SCREEN DEFAULT_SCREEN;
                EASUIvec2 SIZE;
                int RESIZABLE;
                int (*ADD_ELEMENT)(EASUI_WINDOW* WINDOW, void* ELEMENT);
                int (*START)(EASUI_WINDOW* WINDOW);
                void(*UPDATE_SIZE_AND_CONTEXT_SIZE)(EASUI_WINDOW* WINDOW);
                char* TITLE;

                // FOR RENDERING TEST
                EASUIvec3 BG_COLOR;
        };


        int SET_NEW_EASUI_WINDOW(EASUI_WINDOW* WINDOW, const char* TITLE, const unsigned short MAX_ELEMENT_COUNT, const EASUIvec2 SIZE, const int RESIZABLE);

// =============================================================================================================


// =================================================== [FRAME] =================================================

        typedef struct EASUI_FRAME EASUI_FRAME;

        struct EASUI_FRAME 
        {
                
                void** ELEMENT_LIST;
                EASUIvec2 POSITION;
                EASUIvec2 SIZE;
                EASUIvec3 COLOR;
                unsigned int ALPHA;
                
        };

        int 

// ===============================================================================================================

// =================================================== [LABEL] =================================================

        typedef struct EASUI_LABEL EASUI_LABEL;


        struct EASUI_LABEL
        {

                char TYPE;
                unsigned long MAX_STRING_SIZE;
                EASUIvec2 POSITION, SIZE;
                unsigned int FONT_SIZE;
                char* TEXT;
                void (*TEST_FUNCTION)(const EASUI_LABEL* LABEL);

        };


        int SET_NEW_EASUI_LABEL(EASUI_LABEL* LABEL, void* OPTIONAL__FRAMED_HOLDER, const EASUIvec2 POSITION, const EASUIvec2 SIZE, const unsigned int FONT_SIZE, const unsigned long MAX_STRING_SIZE);

// ===============================================================================================================


#endif
