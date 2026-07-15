#include "EASUI/EASUI.h"
#include <stdio.h>



int main()
{

        EASUI_WINDOW TEST_WINDOW;
        EASUI_LABEL TEST_LABEL;


        EASUI_INIT();


        // [RUN PART]
        {

                SET_NEW_EASUI_WINDOW(&TEST_WINDOW, 16, 300, 200);


                printf("ADDRESS OF WINDOW ELEMENT_LIST = %p\n", TEST_WINDOW.ELEMENT_LIST);


                SET_NEW_EASUI_LABEL(&TEST_LABEL, &TEST_WINDOW, 0, 0, 20, 10, 12, 1024);


                printf("ADDRESS OF TEST_LABEL = %p\n", &TEST_LABEL);
                printf("ADDRESS OF WINDOW ELEMENT_LIST[0] (SHOULD BE TEST_LABEL) = %p\n", TEST_WINDOW.ELEMENT_LIST[0]);

        }


        EASUI_END();



        return 0;

}
