# Compiler and Flags
CXX = g++
CXXFLAGS =   -O3  -Wall  -Iheader_files # Add the include path for header files
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

# Main target
all: $(OUTPUT_DIR)/main

# Compile and link the main executable, using the object files
$(OUTPUT_DIR)/main: $(MODULES_DIR)/main.cpp $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^  # Use $^ instead of $<

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

# Ensure the output directory exists
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Clean up all object files and the main executable
clean:
	rm -f $(OBJS) $(OUTPUT_DIR)/main

# Run the compiled program
run: $(OUTPUT_DIR)/main
	./$(OUTPUT_DIR)/main
