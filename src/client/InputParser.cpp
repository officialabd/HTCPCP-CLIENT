#include "../../headers/client/InputParser.h"

void parse(std::string line, char *message, char *port, char *ip) {
    char *method = (char *)calloc(1, 64);
    int potnum;
    std::string temp;
    std::istringstream iss(line);

    getline(iss, temp, ':');
    strcpy(method, temp.c_str());
    getline(iss, temp, ':');
    char *p_temp = (char *)(temp.c_str()) + 2;
    strcpy(ip, p_temp);
    if (!strcmp(ip, "localhost")) {
        strcpy(ip, LOCALHOST);
    }
    std::cout << "BF: " << ip << std::endl;
    getline(iss, temp, '/');
    strcpy(port, temp.c_str());
    getline(iss, temp, '?');
    potnum = strtol(temp.c_str(), NULL, 10);

    char *additions = (char *)calloc(1, MAX_MESSAGE_SIZE);
    char *prev = (char *)calloc(1, MAX_MESSAGE_SIZE);

    while (getline(iss, temp, '#')) {
        strcat(additions, temp.c_str());
        strcat(additions, "#");
    }
    additions[strlen(additions) - 1] = '\0';

    if (!strcmp(method, BREW)) {
        brew(message, potnum, additions);
    } else if (!strcmp(method, POST)) {
        post(message, potnum, additions);
    } else if (!strcmp(method, PROPFIND)) {
        propfind(message, potnum, additions);
    } else {
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
    sprintf(message_temp, "POST pot-%d HTCPCP/1.0\r\nAccept-Additions:%s\r\n", potnum, additions);
    sprintf(message, "%sContent-Type: message/coffeepot\r\nContent-Length: %ld\r\n\r\nstart\r\n", message_temp, strlen(message_temp));
    return message;
}

char *propfind(char *message, int potnum, char *additions) {
    sprintf(message, "PROPFIND pot-%d HTCPCP/1.0\r\n", potnum);
    return message;
}
