#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#define CHAR_SIZE 1
#define MAX_ERROR_MESSAGE 1024
#define ERROR -1

void errorHandler(int val, char *err);
