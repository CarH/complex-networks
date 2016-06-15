LIBS_PATH=libs

INCLUDE_GRAPH_PATH=libs/Graph/include
SRC_GRAPH_PATH=libs/Graph/src/Graph.cpp
INCLUDE_COMPLEX_NET_PATH=libs/ComplexNetwork/include
SRC_COMPLEX_NET_PATH=libs/ComplexNetwork/src/ComplexNetwork.cpp
LIBRARIES_PATH=libraries/
CC=g++
CFLAGS=-c -Wall -g
NSAMPLES = 10

all: clean mkdirGeneratedDatasets mkdirLibraries compile

mkdirGeneratedDatasets:
	mkdir -p generatedDatasets
mkdirLibraries:
	mkdir libraries

compile: main.o generateSamples.o
	$(CC) $(LIBRARIES_PATH)main.o $(LIBRARIES_PATH)Graph.o $(LIBRARIES_PATH)ComplexNetwork.o -o prog
	$(CC) $(LIBRARIES_PATH)generateSamples.o $(LIBRARIES_PATH)Graph.o -o generateSamples

Graph.o:
	$(CC) $(CFLAGS) -I./$(LIBS_PATH) $(SRC_GRAPH_PATH)
	mv *.o libraries/

ComplexNetwork.o:
	$(CC) $(CFLAGS) -I./$(LIBS_PATH) -I./$(INCLUDE_GRAPH_PATH) $(SRC_COMPLEX_NET_PATH)
	mv *.o libraries/

main.o: Graph.o ComplexNetwork.o
	$(CC) $(CFLAGS) -I./$(INCLUDE_GRAPH_PATH) -I./$(INCLUDE_COMPLEX_NET_PATH) src/main.cpp
	mv *.o libraries/

generateSamples.o: Graph.o
	$(CC) $(CFLAGS) -I./$(INCLUDE_GRAPH_PATH) -I./$(INCLUDE_COMPLEX_NET_PATH) src/generateSamples.cpp
	mv *.o libraries/
test:
	#######################################
	# Executing Test 1: Facebook dataset
	@./prog dataset/facebook.links facebook
	@echo
	#######################################
	# Executing Test 2: Foursquare dataset
	@./prog dataset/foursquare.links foursquare
	@echo
	#######################################
	# Executing Test 3: GPlus dataset
	@./prog dataset/gplus.links gplus
	@echo
	#######################################
	# Executing Test 4: Test dataset
	@./prog dataset/test.links test_

	@mkdir -p reports
	@mv *.out ./reports
genSamples:
	#######################################
	# Generating Samples for Facebook dataset
	@./generateSamples dataset/facebook.links facebook $(NSAMPLES)
	@echo
	#######################################
	# Generating Samples for Foursquare dataset
	@./generateSamples dataset/foursquare.links foursquare $(NSAMPLES)
	@echo
	#######################################
	# Generating Samples for GPlus dataset
	@./generateSamples dataset/gplus.links gplus $(NSAMPLES)
	
	@mv *.links ./generatedDatasets
clean:
	rm -rf libraries/ *.o prog generateSamples 

