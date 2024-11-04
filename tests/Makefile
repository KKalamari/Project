# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g  # Enable warnings and debugging symbols

# The target executable names
READING_TARGET = reading_test 
GRAPH_TARGET = graph_test
ROBUST_EXT_TARGET= robust_ext_test
EUCLIDEAN_TARGET= euclidean_test
GREEDY_TARGET= greedysearch_test
MEDOID_TARGET = medoid_test

# The source files
READING_SRCS = reading_test.cpp  ./../modules/reading.cpp
GRAPH_SRCS = graph_test.cpp ./../modules/graph_creation.cpp #include graph_creationg to the test
ROBUST_EXT_SRCS = robust_ext_test.cpp ./../modules/robust_ext.cpp ./../modules/euclidean_distance.cpp
EUCLIDEAN_SRCS = euclidean_test.cpp ./../modules/euclidean_distance.cpp 
GREEDY_SRCS = greedysearch_test.cpp ./../modules/greedysearch.cpp ./../modules/euclidean_distance.cpp ./../modules/reading.cpp# Add graph_creation.cpp to MEDOID_SRCS to link with medoid_test
MEDOID_SRCS = medoid_test.cpp ./../modules/vamana.cpp ./../modules/euclidean_distance.cpp ./../modules/graph_creation.cpp ./../modules/robust_ext.cpp ./../modules/greedysearch.cpp

# Acutest include directory
ACUTEST_DIR = ./../header_files  # Path to the directory with header files
ACUTEST_FLAGS = -I$(ACUTEST_DIR)  # Include Acutest header
GRAPH_CREATION_DIR = ./../header_files  # Directory for graph_creation.h (and not only graph creation)
EUCLIDEAN_DISTANCE_DIR = ./../header_files  # Directory for euclidean_distance.h
ROBUST_EXT_DIR= ./../header_files 
MEDOID_DIR=./../header_files

# The target rule to build the executables
all: $(GRAPH_TARGET) $(READING_TARGET) $(EUCLIDEAN_TARGET) $(GREEDY_TARGET) $(ROBUST_EXT_TARGET) $(MEDOID_TARGET) 

$(GREEDY_TARGET): $(GREEDY_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(EUCLIDEAN_DISTANCE_DIR) -o $(GREEDY_TARGET) $(GREEDY_SRCS)

$(EUCLIDEAN_TARGET): $(EUCLIDEAN_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(EUCLIDEAN_DISTANCE_DIR) -o $(EUCLIDEAN_TARGET) $(EUCLIDEAN_SRCS)

$(READING_TARGET): $(READING_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(GRAPH_CREATION_DIR) -I$(EUCLIDEAN_DISTANCE_DIR) -o $(READING_TARGET) $(READING_SRCS)

$(GRAPH_TARGET): $(GRAPH_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(GRAPH_CREATION_DIR) -I$(EUCLIDEAN_DISTANCE_DIR) -o $(GRAPH_TARGET) $(GRAPH_SRCS)

$(ROBUST_EXT_TARGET): $(ROBUST_EXT_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(ROBUST_EXT_DIR) -o $(ROBUST_EXT_TARGET) $(ROBUST_EXT_SRCS)

$(MEDOID_TARGET): $(MEDOID_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(MEDOID_DIR) -I$(GRAPH_CREATION_DIR) -o $(MEDOID_TARGET) $(MEDOID_SRCS)



clean:
	rm -f $(GRAPH_TARGET) $(READING_TARGET) $(EUCLIDEAN_TARGET) $(GREEDY_TARGET) $(ROBUST_EXT_TARGET) $(MEDOID_TARGET) 

run: $(GRAPH_TARGET) $(READING_TARGET) $(EUCLIDEAN_TARGET) $(GREEDY_TARGET) $(ROBUST_EXT_TARGET) 
	./$(GRAPH_TARGET)
	./$(READING_TARGET)
	./$(EUCLIDEAN_TARGET)
	./$(GREEDY_TARGET)
	./$(ROBUST_EXT_TARGET)
	./$(VAMANA_TARGET)
