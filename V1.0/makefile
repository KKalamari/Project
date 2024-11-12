# Compiler and Flags
CXX = g++
CXXFLAGS = -O3  -std=c++17  -Iheader_files # Add the include path for header files
OUTPUT_DIR = output
MODULES_DIR = modules
TESTS_DIR = tests

.PHONY: all clean run

# Object files
OBJS = $(OUTPUT_DIR)/graph_creation.o \
       $(OUTPUT_DIR)/euclidean_distance.o \
       $(OUTPUT_DIR)/reading.o \
       $(OUTPUT_DIR)/greedysearch.o \
       $(OUTPUT_DIR)/robust_ext.o \
       $(OUTPUT_DIR)/vamana.o \
       $(OUTPUT_DIR)/for_binary.o

# Main target
all: $(OUTPUT_DIR)/main

# Compile and link the main executable using the object files
$(OUTPUT_DIR)/main: $(MODULES_DIR)/main.cpp $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each module source file into an object file in the output directory
$(OUTPUT_DIR)/graph_creation.o: $(MODULES_DIR)/graph_creation.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/reading.o: $(MODULES_DIR)/reading.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/euclidean_distance.o: $(MODULES_DIR)/euclidean_distance.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/greedysearch.o: $(MODULES_DIR)/greedysearch.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/robust_ext.o: $(MODULES_DIR)/robust_ext.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/vamana.o: $(MODULES_DIR)/vamana.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile for_binary module for binary file I/O
$(OUTPUT_DIR)/for_binary.o: $(MODULES_DIR)/for_binary.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Create the output directory if it doesn't exist
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Clean up the output files
clean:
	rm -f $(OBJS) $(OUTPUT_DIR)/main

# Run the main executable
run: $(OUTPUT_DIR)/main
	./$(OUTPUT_DIR)/main
