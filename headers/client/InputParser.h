#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#define MAX_MESSAGE_SIZE 4096
#define BREW "BREW"
#define POST "POST"
#define PROPFIND "PROPFIND"
#define LOCALHOST "127.0.0.1"

void parse(std::string line, char *message, char *port, char *ip);

char *brew(char *message, int potnum, char *additions);

char *post(char *message, int potnum, char *additions);

char *propfind(char *message, int potnum, char *additions);