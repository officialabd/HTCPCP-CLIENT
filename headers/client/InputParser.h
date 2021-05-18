#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>

#define MAX_MESSAGE_SIZE 4096
#define BREW "brew"
#define POST "post"
#define PROPFIND "propfind"
#define COFFEE "coffee"
#define LOCALHOST "127.0.0.1"

#define SUCCESSFUL 1
#define BAD_URL 0

/**
 * This function parse the client URL and maintain the request.
 * @param line String of the client URL.
 * @param message string of the request message.
 * @param port int port of the server.
 * @param ip string address of the server. 
 * @return int 1 on successful URI parsing and store the response in message, otherwise return 0 on error.
 */
int parse(std::string line, char *message, char *port, char *ip);

/**
 * This function prepares the client request with brew method.
 * @param message string of the final request.
 * @param potnum int of the pot.
 * @param additions string of the additions.
 * @return String of the request.
 */
char *brew(char *message, int potnum, char *additions);

/**
 * This function prepares the client request with post method.
 * @param message string of the final request.
 * @param potnum int of the pot.
 * @param additions string of the additions.
 * @return String of the request.
 */
char *post(char *message, int potnum, char *additions);

/**
 * This function prepares the client request with propfind method.
 * @param message string of the final request.
 * @param potnum int of the pot.
 * @param additions string of the additions.
 * @return String of the request.
 */
char *propfind(char *message, int potnum, char *additions);