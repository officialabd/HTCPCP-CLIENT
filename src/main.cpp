
#include <time.h>

#include <iostream>
#include <string>

#include "../headers/client/Client.h"
#include "../headers/client/InputParser.h"

#define EXIT "exit"
#define DEBUG "d"
#define MULTI "m"

char *debug(int num);
void *thread(void *arg);

int main(int argc, char *argv[]) {
    char *port = (char *)calloc(1, 64);
    char *ip = (char *)calloc(1, 128);
    char *message = (char *)calloc(1, MAX_MESSAGE_SIZE * 4);
    int connected = 0;

    std::cout << "\tHyper Text Coffee Pot\n"
              << "\t   WELCOME CLIENT\n"
              << "\t     coffee-scheme: [//host][/pot-designator][?additions-list]"
              << std::endl;

    while (true) {
        std::cout << "--------------------------------> (^-^): " << std::endl;
        memset(message, 0, MAX_MESSAGE_SIZE * 4);
        std::string line("");

        getline(std::cin, line);
        if (!strcmp(line.c_str(), EXIT)) {  // If client enter exit then it will exit.
            closeSocket();
            break;
        } else if (!strcmp(line.substr(0, 1).c_str(), DEBUG)) {  // For debugging (d *)
            int num = atoi((line.c_str() + 2));
            if (num < 6) {
                line = debug(num);
                parse(line, message, port, ip);
            } else {
                strcpy(message, debug(num));
            }
        } else {  // when client enter uri
            parse(line, message, port, ip);
        }

        if (!connected) {
            connectClient(atoi(port), ip);  // connect to the server
            connected = 1;
        }
        if (message != NULL) {
            std::cout << "URI: " << line << std::endl;
            communicate(message);  // Communicate with the server
        }
    }

    return 0;
}
// Used to test and debug requests the uri
char *debug(int num) {
    switch (num) {
        case -1:
            return (char *)"BREW://178.130.187.165:54000/1?";
        case 1:
            return (char *)"BREW://127.0.0.1:9905/1?#Almond;2#Vanilla;5#almond;2";
        case 2:
            return (char *)"BREW://127.0.0.1:9905/2?";
        case 3:
            return (char *)"POST://localhost:9905/3?#Almond;2";
        case 4:
            return (char *)"POST://localhost:9905/2?#Almond;2#Vanilla;5#almond;2";
        case 5:
            return (char *)"PROPFIND://localhost:9905/";
        case 10:
            return (char *)"POT pot-1 HTCPCP/1.0\r\nAccept-Additions: \r\nContent-Type: message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 11:
            return (char *)"POST pot6 HTCPCP/1.0\r\nAccept-Additions: \r\nContent-Type: message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 12:
            return (char *)"POST pot-6 HTCPCP/1.0\r\nAccept-Additions: \r\nContent-Type: message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 13:
            return (char *)"POST  HTCPCP/1.0\r\nAccept-Additions: \r\nContent-Type: message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 14:
            return (char *)"POST pot-5 HTCPCP/1.1\r\nAccept-Additions: \r\nContent-Type: message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 15:
            return (char *)"POST pot-2 HTCPCP/1.0\r\nAcceptAdditions: \r\nContent-Type: message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 16:
            return (char *)"POST pot-3 HTCPCP/1.0\r\nAccept-Additions: \rContent-Type: message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 17:
            return (char *)"POST pot-1 HTCPCP/1.0\r\nAccept-Additions: \r\nContent-Type:message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 18:
            return (char *)"POST pot-4 HTCPCP/1.0\r\nAccept-Additions: \r\nContent-Type: message/coffeepot\r\nContent-Length: -1\r\n\r\nstart\r\n";
        case 19:
            return (char *)"POST pot-5 HTCPCP/1.0\r\nAccept-Additions: \r\nContent-Type: message/coffeepotContent-Length: 0\r\nsTart\r\n";
        case 20:
            return (char *)"POST pot-5 HTCPCP/1.0\r\nAccept-Additions: #Almond;2#Vanilla;5\r\nContent-Type: message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 21:
            return (char *)"POST pot-5 HTCPCP/1.0\r\nAccept-Additions: Almond;2#Vanilla;5\r\nContent-Type: message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 22:
            return (char *)"POST pot-5 HTCPCP/1.0\r\nAccept-Additions: #Almond2#Vanilla;5\r\nContent-Type: message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 23:
            return (char *)"POST pot-5 HTCPCP/1.0\r\nAccept-Additions: #Almond;2#Vanilla;\r\nContent-Type: message/coffeepot\r\nContent-Length: 0\r\n\r\nstart\r\n";
        case 24:
            return (char *)"POST pot-5 HTCPCP/1.0\r\nAccept-Additions: #Almond;2#Vanilla;5\r\nContent-Type: message/coffeepot\r\nContent-Length: 0\r\nstart\r\n";
    }
    return NULL;
}