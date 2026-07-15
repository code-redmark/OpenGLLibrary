#include "../EASUI.h"




void TEST_FUNCTION(const EASUI_LABEL* LABEL);




int SET_NEW_EASUI_LABEL(EASUI_LABEL* LABEL, void* FRAMED_HOLDER, const unsigned int X_POSITION, const unsigned int Y_POSITION, const unsigned int WIDTH, const unsigned int HEIGHT, const unsigned int FONT_SIZE, const unsigned long MAX_STRING_SIZE)
{

        // [SET GIVEN VALUES AND FUNCTIONS]
        {

                LABEL->TYPE = EASUI_LABEL_NUMBER;
                LABEL->X_POSITION = X_POSITION;
                LABEL->Y_POSITION = Y_POSITION;
                LABEL->WIDTH = WIDTH;
                LABEL->HEIGHT = HEIGHT;
                LABEL->FONT_SIZE = FONT_SIZE;
                LABEL->MAX_STRING_SIZE = MAX_STRING_SIZE;
                LABEL->TEST_FUNCTION = TEST_FUNCTION;

        }


        if (LABEL == NULL || FRAMED_HOLDER == NULL)
        {

                return EASUI_ERROR;

        }


        ADD__ELEMENT__TO__FRAMED_ELEMENT(FRAMED_HOLDER, LABEL);


        // [ALLOCATE MEMORY FOR THE TEXT]
        {

                LABEL->TEXT = malloc(MAX_STRING_SIZE);


                if (LABEL->TEXT == NULL)
                {

                        return EASUI_ERROR;

                }


                LABEL->TEXT[0] = '\0';

        }


        return EASUI_OK;

}


void TEST_FUNCTION(const EASUI_LABEL* LABEL)
{

        printf("%s\n", LABEL->TEXT);

}
