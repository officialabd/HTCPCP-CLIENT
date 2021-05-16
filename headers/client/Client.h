#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "../handlers/ErrorHandler.h"

/** Used to specify the message size*/
#define MAX_MESSAGE_SIZE 4096

/**
 * It connects the client to the server on the port and ip.
 * @param port int of the port of the server.
 * @param ip string of the ip address of the server.
 * @return No return value (void).
*/
void connectClient(int port, char *ip);

/**
 * It communicates with the server, send mess, and receive.
 * @param mess string of the message to be sent. 
 * @return No return value (void).
*/
void communicate(char *mess);

/**
 * It sends the message to the server on the socket.
 * @param socket int of the client socket connected to the server. 
 * @param buf string of the message.
 * @param flags the flags to specify the sending.
 * @return No return value (void).
*/
void send(int socket, char *buf, int flags);

/**
 * It receives the response from the server on the socket.
 * @param socket int of the client socket connected to the server. 
 * @param buf string of the response.
 * @param flags the flags to specify the sending.
 * @return String of the response.
*/
char *receive(int socket, char *buf, int flags);

/**
 * It closes the client socket to disconnect from the server.
 * @return No return value (void).
*/
void closeSocket();