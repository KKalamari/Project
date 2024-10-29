CXX = g++
CXXFLAGS = -Wall -Iheader_files  # Add the include path for header files
OUTPUT_DIR = output
MODULES_DIR = modules
TESTS_DIR = tests

.PHONY: all clean

# Object files
OBJS = $(OUTPUT_DIR)/graph_creation.o $(OUTPUT_DIR)/euclidean_distance.o $(OUTPUT_DIR)/reading.o $(OUTPUT_DIR)/greedysearch.o $(OUTPUT_DIR)/vamana.o

# Main target
all: $(OUTPUT_DIR)/main

# Compile and link the main executable, using the object files
$(OUTPUT_DIR)/main: $(MODULES_DIR)/main.cpp $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJS)

# Compile graph_creation.cpp into an object file
$(OUTPUT_DIR)/graph_creation.o: $(MODULES_DIR)/graph_creation.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile reading.cpp into an object file
$(OUTPUT_DIR)/reading.o: $(MODULES_DIR)/reading.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile euclidean_distance.cpp into an object file
$(OUTPUT_DIR)/euclidean_distance.o: $(MODULES_DIR)/euclidean_distance.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile greedysearch.cpp into an object file
$(OUTPUT_DIR)/greedysearch.o: $(MODULES_DIR)/greedysearch.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/vamana.o: $(MODULES_DIR)/vamana.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Ensure the output directory exists
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

clean:
	rm -f $(OUTPUT_DIR)/euclidean_distance.o $(OUTPUT_DIR)/graph_creation.o $(OUTPUT_DIR)/reading.o $(OUTPUT_DIR)/greedysearch.o $(OUTPUT_DIR)/vamana.o $(OUTPUT_DIR)/main