# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g  # Enable warnings and debugging symbols

# The target executable names
GREEDY_TARGET = greedy
ROBUST_TARGET = robust_test  # Renamed to clarify it’s for tests

# The source files
GREEDY_SRCS = greedy.cpp ./../modules/graph_creation.cpp
ROBUST_SRCS = robust_test.cpp ./../modules/robust.cpp  # Include robust.cpp for the test

# Acutest include directory
ACUTEST_DIR = ./../header_files  # Path to the directory with header files
ACUTEST_FLAGS = -I$(ACUTEST_DIR)  # Include Acutest header
GRAPH_CREATION_DIR = ./../header_files  # Directory for graph_creation.h
EUCLIDEAN_DISTANCE_DIR = ./../header_files  # Directory for euclidean_distance.h
ROBUST_DIR = ./../modules  # Directory for the robust module

# The target rule to build the executables
all: $(GREEDY_TARGET) $(ROBUST_TARGET)

$(GREEDY_TARGET): $(GREEDY_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(GRAPH_CREATION_DIR) -I$(EUCLIDEAN_DISTANCE_DIR) -o $(GREEDY_TARGET) $(GREEDY_SRCS)

$(ROBUST_TARGET): $(ROBUST_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(ROBUST_DIR) -o $(ROBUST_TARGET) $(ROBUST_SRCS)

# Rule to clean up the compiled output
clean:
	rm -f $(GREEDY_TARGET) $(ROBUST_TARGET)

# Rule to run the tests
run: $(GREEDY_TARGET) $(ROBUST_TARGET)
	./$(GREEDY_TARGET)
	./$(ROBUST_TARGET) 
