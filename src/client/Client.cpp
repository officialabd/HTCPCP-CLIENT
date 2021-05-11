#include "../../headers/client/Client.h"

int sck;

void connectClient(int port, char *ip) {
    int re = 0;
    sck = socket(AF_INET, SOCK_STREAM, 0);
    errorHandler(sck, (char *)"Create client socket failed");

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);
    std::cout << port << "   " << ip << "   " << sck << std::endl;

    re = connect(sck, (sockaddr *)&addr, sizeof(addr));
    errorHandler(re, (char *)"Connecting failed");
    std::cout << "4" << std::endl;
}

void communicate(std::string mess) {
    char *buf = (char *)calloc(sizeof(char), MAX_MESSAGE_SIZE * 4);

    send(sck, (char *)mess.c_str(), 0);
    memset(buf, 0, MAX_MESSAGE_SIZE * 4);
    buf = receive(sck, buf, 0);
    std::cout << "TEST" << buf << std::endl;

    if (buf != NULL) {
        std::cout << buf << std::endl;
    } else {
        return;
    }
}

void send(int socket, char *buf, int flags) {
    if (send(socket, buf, strlen(buf), flags) == ERROR) {
        perror("Client (sending failed)");
    }
}

char *receive(int socket, char *buf, int flags) {
    int re = recv(socket, buf, MAX_MESSAGE_SIZE * 4, flags);
    if (re == ERROR) {
        std::cout << "Recieving from the server failed" << std::endl;
        return NULL;
    } else if (re == 0) {
        std::cout << "Server disconnected" << std::endl;
        return NULL;
    } else {
        return buf;
    }
}

void closeSocket() {
    close(sck);
}