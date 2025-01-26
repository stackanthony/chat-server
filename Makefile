CXX = g++
CXXFLAGS = -Wall -std=c++17 -I classes -I models  # Added -I models

# Find all cpp files excluding main files
COMMON_SRCS := $(shell find classes models -name '*.cpp')  # Added models
COMMON_OBJS := $(COMMON_SRCS:.cpp=.o)

# Server specific
SERVER_SRCS := server.cpp $(COMMON_SRCS)
SERVER_OBJS := $(SERVER_SRCS:.cpp=.o)

# Client specific
CLIENT_SRCS := client.cpp $(COMMON_SRCS)
CLIENT_OBJS := $(CLIENT_SRCS:.cpp=.o)

all: server client

server: $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

client: $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run-server:
	./server

run-client:
	./client

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) server client
