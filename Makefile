.PHONY: all

all: 
	g++ -std=c++2a ipkcpc.cpp tcp.cpp udp.cpp -o ipkcpc 

