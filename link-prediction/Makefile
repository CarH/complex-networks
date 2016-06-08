LIBS=libs/graph
INCLUDE_PATH=libs/
CC=g++
CFLAGS=-c -Wall

all: clean compile

compile: libraries main.o
	$(CC) -I./libraries main.o -o prog

libraries:
	mkdir libraries/
	for dir in $(LIBS); do \
		cd $$dir; \
		$(CC) $(CFLAGS) src/*.cpp -I../; \
		mv *.o ../../libraries; \
		cd -; \
	done

main.o:
	$(CC) $(CFLAGS) -I./libs/graph/include/ src/main.cpp

clean:
	rm -rf libraries/ main.o prog

