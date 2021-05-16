#include "../../headers/handlers/ErrorHandler.h"

void errorHandler(int val, char *err) {
    if (val == ERROR) {
        char *temp = (char *)calloc(CHAR_SIZE, MAX_ERROR_MESSAGE + strlen(err));
        sprintf(err, "\033[31m%s\033[31m", err);
        perror(err);
    }
}