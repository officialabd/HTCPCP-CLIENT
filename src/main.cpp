
#include <iostream>
#include <string>

#include "../headers/client/Client.h"
#include "../headers/client/InputParser.h"

#define EXIT "exit"

int main(int argc, char *argv[]) {
    char *port = (char *)calloc(1, 64);
    char *ip = (char *)calloc(1, 128);
    char *message = (char *)calloc(1, MAX_MESSAGE_SIZE * 4);
    int connected = 0;

    while (true) {
        memset(message, 0, MAX_MESSAGE_SIZE * 4);
        std::string line;
        getline(std::cin, line);
        if (!strcmp(line.c_str(), EXIT)) {
            break;
        }
        parse(line, message, port, ip);
        if (!connected) {
            connectClient((int)strtol(port, NULL, 10), ip);
            connected = 1;
        }
        communicate(message);
    }

    return 0;
}

//BREW://178.130.187.165:54000/2?Almond;2#Vanilla;5#almond;2
//BREW://localhost:9000/2?Almond;2#Vanilla;5#almond;2
//BREW://127.0.0.1:9905/2?Almond;2#Vanilla;5#almond;2
//POST://178.130.187.165:54000/2?Almond;2#Vanilla;5#almond;2
//PROPFIND://localhost:9905/3
// PROPFIND://178.130.187.165:54000/2