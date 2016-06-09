LIBS=libs/graph
INCLUDE_PATH=libs/graph/include/
LIBRARIES_PATH=libraries/
CC=g++
CFLAGS=-c -Wall

all: clean compile

compile: libraries main.o
	$(CC) $(LIBRARIES_PATH)*.o main.o -o prog

libraries:
	mkdir libraries/
	for dir in $(LIBS); do \
		cd $$dir; \
		$(CC) $(CFLAGS) src/*.cpp -I../; \
		mv *.o ../../libraries; \
		cd -; \
	done

main.o:
	$(CC) $(CFLAGS) -I./$(INCLUDE_PATH) src/main.cpp

test:
	./prog dataset/facebook.links
	./prog dataset/foursquare.links
	./prog dataset/gplus.links

clean:
	rm -rf libraries/ main.o prog

