#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "../handlers/ErrorHandler.h"

#define MAX_MESSAGE_SIZE 4096

void connectClient(int port, char *ip);

void communicate(std::string mess);

void send(int socket, char *buf, int flags);

char *receive(int socket, char *buf, int flags);

void closeSocket();