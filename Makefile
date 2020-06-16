CXXFLAGS=-g -Wall
CXX=g++
LDFLAGS=-pthread

server: main.o chunkencoding.o http_header.o
	$(CXX) $(LDFLAGS) main.o chunkencoding.o http_header.o -o server

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

chunkencoding.o: chunkencoding.cpp chunkencoding.h
	$(CXX) $(CXXFLAGS) -c chunkencoding.cpp

http_header.o: http_header.cpp http_header.h
	$(CXX) $(CXXFLAGS) -c http_header.cpp

clean:
	rm *.o server