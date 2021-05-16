#include "../../headers/client/InputParser.h"

void parse(std::string line, char *message, char *port, char *ip) {
    char *method = (char *)calloc(1, 64);
    int potnum;
    std::string temp;
    std::istringstream iss(line);  // String stream of user uri, used to parse the uri by spaces.

    // Parse method
    getline(iss, temp, ':');
    if (strcasecmp(temp.c_str(), BREW) && strcasecmp(temp.c_str(), POST) && strcasecmp(temp.c_str(), PROPFIND) && strcasecmp(temp.c_str(), COFFEE)) {
        std::cout << "Invalid scheme" << std::endl;
        return;
    }
    strcpy(method, temp.c_str());

    // Parse and check the URI (//)
    getline(iss, temp, ':');
    if (strcmp(temp.substr(0, 2).c_str(), "//")) {
        std::cout << "Invalid URL" << std::endl;
        return;
    }

    // Parse the host ip
    char *p_temp = (char *)(temp.c_str()) + 2;
    strcpy(ip, p_temp);

    // Check if the ip equals localhost and replace it with 127.0.0.1
    if (!strcmp(ip, "localhost")) {
        strcpy(ip, LOCALHOST);
    }

    // Parse the port
    getline(iss, temp, '/');
    strcpy(port, temp.c_str());

    // Parse the pot number
    getline(iss, temp, '?');

    // Check the pot. If no number specify then replace it with (*) for all pots
    if (!strcmp(temp.c_str(), "*") || !strcmp(temp.c_str(), "\0")) {
        potnum = 0;
    } else {
        potnum = atoi(temp.c_str());
    }

    char *additions = (char *)calloc(1, MAX_MESSAGE_SIZE);
    char *prev = (char *)calloc(1, MAX_MESSAGE_SIZE);

    // Parse additions
    while (getline(iss, temp, '#')) {
        strcat(additions, temp.c_str());
        strcat(additions, "#");
    }
    additions[strlen(additions) - 1] = '\0';

    // Build the request
    if (!strcasecmp(method, BREW)) {
        brew(message, potnum, additions);
    } else if (!strcasecmp(method, POST)) {
        post(message, potnum, additions);
    } else if (!strcasecmp(method, PROPFIND)) {
        propfind(message, potnum, additions);
    } else {
        std::cout << "Method not supported" << std::endl;
        message = NULL;
        return;
    }
}

char *brew(char *message, int potnum, char *additions) {
    char *message_temp = (char *)calloc(sizeof(char), MAX_MESSAGE_SIZE * 2);
    sprintf(message_temp, "BREW pot-%d HTCPCP/1.0\r\nAccept-Additions: %s\r\n", potnum, additions);
    sprintf(message, "%sContent-Type: message/coffeepot\r\nContent-Length: %ld\r\n\r\nstart\r\n", message_temp, strlen(message_temp));
    return message;
}

char *post(char *message, int potnum, char *additions) {
    char *message_temp = (char *)calloc(sizeof(char), MAX_MESSAGE_SIZE * 2);
    sprintf(message_temp, "POST pot-%d HTCPCP/1.0\r\nAccept-Additions: %s\r\n", potnum, additions);
    sprintf(message, "%sContent-Type: message/coffeepot\r\nContent-Length: %ld\r\n\r\nstart\r\n", message_temp, strlen(message_temp));
    return message;
}

char *propfind(char *message, int potnum, char *additions) {
    if (!potnum) {
        sprintf(message, "PROPFIND * HTCPCP/1.0\r\n");
    } else {
        sprintf(message, "PROPFIND pot-%d HTCPCP/1.0\r\n", potnum);
    }
    return message;
}
