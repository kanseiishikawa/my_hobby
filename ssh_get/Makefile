CC = g++ -std=c++17
LIBS = -lcurl

main: main.o file_send.o ssh_search.o
	$(CC) -o main main.o file_send.o ssh_search.o $(LDFLAGS) $(LIBS)

main.o: main.cpp
	$(CC) -c main.cpp $(CXXFLAGS)

file_send.o: file_send.cpp
	$(CC) -c file_send.cpp $(CXXFLAGS)

ssh_search.o: ssh_search.cpp
	$(CC) -c ssh_search.cpp

clean:
