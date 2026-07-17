#include "../EASUI.h"


int SET_LABEL_TEXT(EASUI_LABEL* LABEL, const char* TEXT);
void PRINT_LABEL(const EASUI_LABEL* LABEL);

int SET_NEW_EASUI_LABEL(EASUI_LABEL* LABEL, EASUI_CONTAINER* PARENT, const EASUIvec2 POSITION, const EASUIvec2 SIZE, const uint8_t FONT_SIZE)
{
        // [SET GIVEN VALUES AND FUNCTIONS]
        {
                LABEL->TYPE = E_EASUI_LABEL;
                LABEL->POSITION = POSITION;
                LABEL->SIZE = SIZE;
                LABEL->FONT_SIZE = FONT_SIZE;
                LABEL->PRINT = PRINT_LABEL;
                LABEL->TEXT = malloc(1);
                LABEL->SET_TEXT = SET_LABEL_TEXT;
        }


        if (LABEL == NULL || PARENT == NULL) return EASUI_ERROR;

        PARENT->ADD_ELEMENT(PARENT, (EASUI_ELEMENT*)LABEL);

        return EASUI_OK;
}


void PRINT_LABEL(const EASUI_LABEL* LABEL)
{
    if (LABEL->TEXT == NULL) printf("Label has no text");

    printf("%s\n", LABEL->TEXT);
}

int SET_LABEL_TEXT(EASUI_LABEL* LABEL, const char* TEXT)
{
    if (TEXT == NULL) {
        free(LABEL->TEXT);
        LABEL->TEXT = NULL;
        return EASUI_OK;
    }

    char* temp = realloc(LABEL->TEXT, sizeof(char) * (size_t)(STRING_LENGTH(TEXT) + 1));
    if (temp == NULL) { perror("SET_TEXT ERROR"); return EASUI_ERROR; }

    LABEL->TEXT = temp;
    STRING_COPY(LABEL->TEXT, TEXT);

    return EASUI_OK;
}