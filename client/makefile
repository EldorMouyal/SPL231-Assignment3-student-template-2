CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -lpthread

all: StompWCIClient

EchoClient: bin/ConnectionHandler.o bin/echoClient.o
	g++ -o bin/EchoClient bin/ConnectionHandler.o bin/echoClient.o $(LDFLAGS)

StompWCIClient: bin/ConnectionHandler.o bin/StompClient.o bin/event.o bin/FileReaderWriter.o bin/stompFrame.o bin/StompProtocol.o 
	g++ -o bin/StompWCIClient bin/ConnectionHandler.o bin/event.o bin/FileReaderWriter.o bin/StompClient.o bin/stompFrame.o bin/StompProtocol.o $(LDFLAGS)

bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/echoClient.o: src/echoClient.cpp
	g++ $(CFLAGS) -o bin/echoClient.o src/echoClient.cpp

bin/event.o: src/event.cpp
	g++ $(CFLAGS) -o bin/event.o src/event.cpp

bin/FileReaderWriter.o: src/FileReaderWriter.cpp
	g++ $(CFLAGS) -o bin/FileReaderWriter.o src/FileReaderWriter.cpp

bin/StompClient.o: src/StompClient.cpp
	g++ $(CFLAGS) -o bin/StompClient.o src/StompClient.cpp

bin/stompFrame.o: src/stompFrame.cpp
	g++ $(CFLAGS) -o bin/stompFrame.o src/stompFrame.cpp

bin/StompProtocol.o: src/StompProtocol.cpp
	g++ $(CFLAGS) -o bin/StompProtocol.o src/StompProtocol.cpp
	



.PHONY: clean
clean:
	rm -f bin/*
	