LIBS_PATH=libs

INCLUDE_GRAPH_PATH=libs/Graph/include
SRC_GRAPH_PATH=libs/Graph/src/Graph.cpp
INCLUDE_COMPLEX_NET_PATH=libs/ComplexNetwork/include
SRC_COMPLEX_NET_PATH=libs/ComplexNetwork/src/ComplexNetwork.cpp
LIBRARIES_PATH=libraries/
CC=g++
CFLAGS=-c -Wall -g
NSAMPLES = 1
CONSIDER_CONN_COMP = 1
PREPROC_MIN_DEGREE = 3
PREPROC_NUM_EDGES = 10
PREPROC_TOP_N_DEG = 3

all: clean mkdirGeneratedDatasets mkdirLibraries compile

mkdirGeneratedDatasets:
	mkdir -p generatedDatasets
mkdirLibraries:
	mkdir libraries

compile: main.o generateSamples.o preProc.o
	$(CC) $(LIBRARIES_PATH)main.o $(LIBRARIES_PATH)Graph.o $(LIBRARIES_PATH)ComplexNetwork.o -o prog
	$(CC) $(LIBRARIES_PATH)generateSamples.o $(LIBRARIES_PATH)Graph.o -o generateSamples
	$(CC) $(LIBRARIES_PATH)preProc.o $(LIBRARIES_PATH)Graph.o -o preProc

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
preProc.o: Graph.o
	$(CC) $(CFLAGS) -I./$(INCLUDE_GRAPH_PATH) -I./$(INCLUDE_COMPLEX_NET_PATH) src/preProc.cpp
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
	# @./prog dataset/test.links test_

	#######################################
	# Executing Test 4: Tosco dataset
	@./prog dataset/tosco.links tosco
	@echo

	#######################################
	# Executing Test 2: Foursquare dataset
	# @./prog dataset/foursquare.links foursquare
	@echo
	#######################################
	# Executing Test 3: GPlus dataset
	# @./prog dataset/gplus.links gplus
	@echo
	#######################################
	# Executing Test 4: Test dataset
	# @./prog dataset/test.links test_
	# @./prog generatedDatasets/facebook_TrainingSample_0.links facebook_TrainingSample_0

	@mkdir -p reports
	@mv *.out ./reports
genSamples:
	#######################################
	# Generating Samples for Facebook dataset
	# _PreProc_Edge_
	@./generateSamples dataset/facebook.links facebook $(NSAMPLES) 0
	@./generateSamples dataset/facebook.links facebook $(NSAMPLES) 1

	@./generateSamples generatedDatasets/facebook_PreProc_Edge_.links facebook_PreProc_Edge_ $(NSAMPLES) 0
	@./generateSamples generatedDatasets/facebook_PreProc_Edge_.links facebook_PreProc_Edge_ $(NSAMPLES) 1

	@./generateSamples generatedDatasets/facebook_PreProc_Vert_.links facebook_PreProc_Vert_ $(NSAMPLES) 0
	@./generateSamples generatedDatasets/facebook_PreProc_Vert_.links facebook_PreProc_Vert_ $(NSAMPLES) 1
	@echo
	#######################################
	# Generating Samples for Foursquare dataset
	@./generateSamples dataset/foursquare.links foursquare $(NSAMPLES) 0
	@./generateSamples dataset/foursquare.links foursquare $(NSAMPLES) 1

	@./generateSamples generatedDatasets/foursquare_PreProc_Edge_.links foursquare_PreProc_Edge_ $(NSAMPLES) 0
	@./generateSamples generatedDatasets/foursquare_PreProc_Edge_.links foursquare_PreProc_Edge_ $(NSAMPLES) 1

	@./generateSamples generatedDatasets/foursquare_PreProc_Vert_.links foursquare_PreProc_Vert_ $(NSAMPLES) 0
	@./generateSamples generatedDatasets/foursquare_PreProc_Vert_.links foursquare_PreProc_Vert_ $(NSAMPLES) 1
	@echo
	#######################################
	# Generating Samples for GPlus dataset
	@./generateSamples dataset/gplus.links gplus $(NSAMPLES) 0
	@./generateSamples dataset/gplus.links gplus $(NSAMPLES) 1

	@./generateSamples generatedDatasets/gplus_PreProc_Edge_.links gplus_PreProc_Edge_ $(NSAMPLES) 0
	@./generateSamples generatedDatasets/gplus_PreProc_Edge_.links gplus_PreProc_Edge_ $(NSAMPLES) 1

	@./generateSamples generatedDatasets/gplus_PreProc_Vert_.links gplus_PreProc_Vert_ $(NSAMPLES) 0
	@./generateSamples generatedDatasets/gplus_PreProc_Vert_.links gplus_PreProc_Vert_ $(NSAMPLES) 1

	#######################################
	# # Generating Samples for Test dataset
	# @./generateSamples dataset/test.links test $(NSAMPLES) 0
	# @./generateSamples dataset/test.links test $(NSAMPLES) 1

	# @./generateSamples generatedDatasets/test_PreProc_Edge_.links test_PreProc_Edge_ $(NSAMPLES) 0
	# @./generateSamples generatedDatasets/test_PreProc_Edge_.links test_PreProc_Edge_ $(NSAMPLES) 1

	# @./generateSamples generatedDatasets/test_PreProc_Vert_.links test_PreProc_Vert_ $(NSAMPLES) 0
	# @./generateSamples generatedDatasets/test_PreProc_Vert_.links test_PreProc_Vert_ $(NSAMPLES) 1
	
	@mv *.links ./generatedDatasets
preProcExec:
	#######################################
	# PreProc for Facebook dataset
	# _PreProc_Edge_
	@./preProc dataset/facebook.links facebook $(PREPROC_MIN_DEGREE) $(PREPROC_NUM_EDGES) $(PREPROC_TOP_N_DEG)
	@echo
	#######################################
	# PreProc for Foursquare dataset
	@./preProc dataset/foursquare.links foursquare $(PREPROC_MIN_DEGREE) $(PREPROC_NUM_EDGES) $(PREPROC_TOP_N_DEG)
	@echo
	#######################################
	# PreProc for GPlus dataset
	@./preProc dataset/gplus.links gplus $(PREPROC_MIN_DEGREE) $(PREPROC_NUM_EDGES) $(PREPROC_TOP_N_DEG)

	#######################################
	# PreProc for Test dataset
	# @./preProc dataset/test.links test $(PREPROC_MIN_DEGREE) $(PREPROC_NUM_EDGES) $(PREPROC_TOP_N_DEG)

	@mv *.links ./generatedDatasets
exec:
	#######################################
	# EXEC for Facebook dataset
	# _PreProc_Edge_
	# NO PREPROC
	@mkdir -p reports

	@./prog generatedDatasets/facebook_TrainingSample_0.links facebook_TrainingSample_0 
	@mv *.out ./reports
	@./prog generatedDatasets/facebook_TrainingSample_0_keepCompConex.links facebook_TrainingSample_0_keepCompConex
	@mv *.out ./reports
	# PREPROC EDGE
	@./prog generatedDatasets/facebook_PreProc_Edge__TrainingSample_0.links facebook_PreProc_Edge__TrainingSample_0 
	@mv *.out ./reports
	@./prog generatedDatasets/facebook_PreProc_Edge__TrainingSample_0_keepCompConex.links facebook_PreProc_Edge__TrainingSample_0_keepCompConex
	# PREPROCVERT
	@./prog generatedDatasets/facebook_PreProc_Vert__TrainingSample_0.links facebook_PreProc_Vert__TrainingSample_0
	@mv *.out ./reports
	@./prog generatedDatasets/facebook_PreProc_Vert__TrainingSample_0_keepCompConex.links facebook_PreProc_Vert__TrainingSample_0_keepCompConex
	@mv *.out ./reports
	@echo
	#######################################
	# EXEC for Foursquare dataset
	# NO PREPROC
	@./prog generatedDatasets/foursquare_TrainingSample_0.links foursquare_TrainingSample_0
	@mv *.out ./reports
	@./prog generatedDatasets/foursquare_TrainingSample_0_keepCompConex.links foursquare_TrainingSample_0_keepCompConex
	@mv *.out ./reports
	# PREPROC EDGE
	@./prog generatedDatasets/foursquare_PreProc_Edge__TrainingSample_0.links foursquare_PreProc_Edge__TrainingSample_0
	@mv *.out ./reports
	@./prog generatedDatasets/foursquare_PreProc_Edge__TrainingSample_0_keepCompConex.links foursquare_PreProc_Edge__TrainingSample_0_keepCompConex
	@mv *.out ./reports
	# PREPROCVERT
	@./prog generatedDatasets/foursquare_PreProc_Vert__TrainingSample_0.links foursquare_PreProc_Vert__TrainingSample_0 
	@mv *.out ./reports
	@./prog generatedDatasets/foursquare_PreProc_Vert__TrainingSample_0_keepCompConex.links foursquare_PreProc_Vert__TrainingSample_0_keepCompConex
	@mv *.out ./reports
	@echo
	#######################################
	# EXEC for GPlus dataset
	# NO PREPROC
	@./prog generatedDatasets/gplus_TrainingSample_0.links gplus_TrainingSample_0 
	@mv *.out ./reports
	@./prog generatedDatasets/gplus_TrainingSample_0_keepCompConex.links gplus_TrainingSample_0_keepCompConex
	@mv *.out ./reports
	# PREPROC EDGE
	@./prog generatedDatasets/gplus_PreProc_Edge__TrainingSample_0.links gplus_PreProc_Edge__TrainingSample_0 
	@mv *.out ./reports
	@./prog generatedDatasets/gplus_PreProc_Edge__TrainingSample_0_keepCompConex.links gplus_PreProc_Edge__TrainingSample_0_keepCompConex
	@mv *.out ./reports
	# PREPROCVERT
	@./prog generatedDatasets/gplus_PreProc_Vert__TrainingSample_0.links gplus_PreProc_Vert__TrainingSample_0 
	@mv *.out ./reports
	@./prog generatedDatasets/gplus_PreProc_Vert__TrainingSample_0_keepCompConex.links gplus_PreProc_Vert__TrainingSample_0_keepCompConex

	@mv *.out ./reports
genSampleTest:
	@./generateSamples dataset/test.links test $(NSAMPLES) 0
runTestTosco:
	# @./prog generatedDatasets/test_TrainingSample_0.links test_TrainingSample_0
getDatabasesProp:
	@./prog dataset/facebook.links facebook
	@./prog generatedDatasets/facebook_PreProc_Vert_.links facebook_PreProc_Vert_
	@./prog generatedDatasets/facebook_PreProc_Edge_.links facebook_PreProc_Edge_ 
	@echo
	#######################################
	# getDataBasesPro for Foursquare dataset
	@./prog dataset/foursquare.links foursquare 
	@./prog generatedDatasets/foursquare_PreProc_Vert_.links foursquare_PreProc_Vert_
	@./prog generatedDatasets/foursquare_PreProc_Edge_.links foursquare_PreProc_Edge_
	@echo
	#######################################
	# getDataBasesPro for GPlus dataset
	@./prog dataset/gplus.links gplus 
	@./prog generatedDatasets/gplus_PreProc_Vert_.links gplus_PreProc_Vert_
	@./prog generatedDatasets/gplus_PreProc_Edge_.links gplus_PreProc_Edge_

	@mv *.out ./reports
	
	
	#######################################
	# getDataBasesPro for Test dataset
	# @./preProc dataset/test.links test $(PREPROC_MIN_DEGREE) $(PREPROC_NUM_EDGES) $(PREPROC_TOP_N_DEG)

clean:
	rm -rf libraries/ *.o prog generateSamples preProc

