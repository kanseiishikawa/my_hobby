CC = g++

main: main.o RSA.o ende_code_file.o search_file.o
	$(CC) -Wall -o main main.o RSA.o ende_code_file.o search_file.o

main.o: main.cpp
	$(CC) -c main.cpp

ende_code_file.o: ende_code_file.cpp
	$(CC) -c ende_code_file.cpp

file_search.o: search_file.cpp
	$(CC) -c search_file.cpp

RSA.o: RSA.cpp
	$(CC) -c RSA.cpp

clean:
	rm *.o
