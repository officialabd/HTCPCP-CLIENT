MAIN = main.cpp
CLIENT = client/Client.cpp client/InputParser.cpp
HANDLERS = handlers/ErrorHandler.cpp 
CC = gcc 
OBJ_NAME_C = ../out/c
FLAGS = -lstdc++ -lpthread

all : compile_client
 
compile_client: $(MAIN) $(CLIENT) $(HANDLERS)
	$(CC) $(MAIN) $(CLIENT) $(HANDLERS) $(UI) $(FLAGS) -o $(OBJ_NAME_C)