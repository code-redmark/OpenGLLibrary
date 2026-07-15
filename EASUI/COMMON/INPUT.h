#ifndef INPUT
#define INPUT



#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


#ifdef _WIN32
    #include <io.h>
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <sys/select.h>
#endif



#define TRUE 1
#define FALSE 0



char PRESSED_KEY(int TO_PRINT);


void WAIT_FOR_KEY(const char TARGET_KEY);


void INPUT_TO_STRING(char* STRING, const char* ALLOWED_KEYS, const unsigned long MAX_LENGTH);




#endif
