.PHONY: all debug release clean

Compiler = g++
RELEASE_FLAGS = -O2 -Wall -DNDEBUG 
DEBUG_FLAGS   = -g -O0 -Wall 

CLIENT_EXEC  = client
SERVER_EXEC  = echo

CLIENT_SRC   = client_echo.cpp
SERVER_SRC   = echo.cpp

BOOST = -lboost_program_options

all: debug release

$(CLIENT_EXEC): $(CLIENT_SRC)
	$(Compiler) $(FLAGS) $(CLIENT_SRC) -o $(CLIENT_EXEC) $(BOOST)

$(SERVER_EXEC): $(SERVER_SRC)
	$(Compiler) $(FLAGS) $(SERVER_SRC) -o $(SERVER_EXEC) $(BOOST)


debug: FLAGS = $(DEBUG_FLAGS)
debug: $(CLIENT_EXEC) $(SERVER_EXEC)

release: FLAGS = $(RELEASE_FLAGS)
release: $(CLIENT_EXEC) $(SERVER_EXEC)

clean:
	rm -f $(CLIENT_EXEC) $(SERVER_EXEC)