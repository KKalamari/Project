# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g  # Enable warnings and debugging symbols

# The target executable name
TARGET = greedy

# The source files
SRCS = greedy.cpp ./../modules/graph_creation.cpp  # Include the graph_creation source file

# Acutest include directory
ACUTEST_DIR = ./../header_files  # Path to the directory with header files
ACUTEST_FLAGS = -I$(ACUTEST_DIR)  # Include Acutest header
GRAPH_CREATION_DIR = ./../header_files  # Directory for graph_creation.h
EUCLIDEAN_DISTANCE_DIR = ./../header_files  # Directory for euclidean_distance.h

# The target rule to build the executable
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(GRAPH_CREATION_DIR) -I$(EUCLIDEAN_DISTANCE_DIR) -o $(TARGET) $(SRCS)

# Rule to clean up the compiled output
clean:
	rm -f $(TARGET)

# Rule to run the tests
run: $(TARGET)
	./$(TARGET)
