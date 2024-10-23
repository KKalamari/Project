# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g  # Enable warnings and debugging symbols

# The target executable names
READING_TARGET = reading_test 
GRAPH_TARGET = graph
ROBUST_TARGET = robust_test  
EUCLIDEAN_TARGET= euclidean_test
GREEDY_TARGET= greedysearch_test

# The source files
READING_SRCS = reading_test.cpp  ./../modules/reading.cpp
GRAPH_SRCS = graph.cpp ./../modules/graph_creation.cpp #include graph_creationg to the test
ROBUST_SRCS = robust_test.cpp ./../modules/robust.cpp  # Include robust.cpp for the test
EUCLIDEAN_SRCS = euclidean_test.cpp ./../modules/euclidean_distance.cpp
GREEDY_SRCS = greedysearch_test.cpp ./../modules/greedysearch.cpp

# Acutest include directory
ACUTEST_DIR = ./../header_files  # Path to the directory with header files
ACUTEST_FLAGS = -I$(ACUTEST_DIR)  # Include Acutest header
GRAPH_CREATION_DIR = ./../header_files  # Directory for graph_creation.h (and not only graph creation)
EUCLIDEAN_DISTANCE_DIR = ./../header_files  # Directory for euclidean_distance.h
ROBUST_DIR = ./../modules  # Directory for the robust module

# The target rule to build the executables
all: $(GRAPH_TARGET) $(ROBUST_TARGET) $(READING_TARGET) $(EUCLIDEAN_TARGET) $(GREEDY_TARGET)

$(GREEDY_TARGET): $(GREEDY_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(EUCLIDEAN_DISTANCE_DIR) -o $(GREEDY_TARGET) $(GREEDY_SRCS)

$(EUCLIDEAN_TARGET): $(EUCLIDEAN_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(EUCLIDEAN_DISTANCE_DIR) -o $(EUCLIDEAN_TARGET) $(EUCLIDEAN_SRCS)

$(READING_TARGET): $(READING_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(GRAPH_CREATION_DIR) -I$(EUCLIDEAN_DISTANCE_DIR) -o $(READING_TARGET) $(READING_SRCS)

$(GRAPH_TARGET): $(GRAPH_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(GRAPH_CREATION_DIR) -I$(EUCLIDEAN_DISTANCE_DIR) -o $(GRAPH_TARGET) $(GRAPH_SRCS)

$(ROBUST_TARGET): $(ROBUST_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(ROBUST_DIR) -o $(ROBUST_TARGET) $(ROBUST_SRCS)

# Rule to clean up the compiled output
clean:
	rm -f $(GRAPH_TARGET) $(ROBUST_TARGET) $(READING_TARGET) $(EUCLIDEAN_TARGET) $(GREEDY_TARGET)

# Rule to run the tests
run: $(GRAPH_TARGET) $(ROBUST_TARGET)
	./$(GRAPH_TARGET)
	./$(ROBUST_TARGET) 
	./$(READING_TARGET)
	./$(EUCLIDEAN_TARGET)
	./$(GREEDY_TARGET)