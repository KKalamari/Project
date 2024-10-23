CXX = g++
CXXFLAGS = -Wall -Iheader_files  
OUTPUT_DIR = output

.PHONY: all clean test

# Object files
OBJS = $(OUTPUT_DIR)/graph_creation.o $(OUTPUT_DIR)/euclidean_distance.o $(OUTPUT_DIR)/reading.o $(OUTPUT_DIR)/greedysearch.o

# Test object files
TEST_OBJS = $(OUTPUT_DIR)/test_greedysearch.o

# Main target
all: $(OUTPUT_DIR)/main

# Compile and link greedysearch, using the object files
$(OUTPUT_DIR)/main: main.cpp $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJS)

# Compile test cases
$(OUTPUT_DIR)/test: $(TEST_OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJS)

# Compile graph_creation.cpp into an object file
$(OUTPUT_DIR)/graph_creation.o: $(MODULES_DIR)/graph_creation.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile euclidean_distance.cpp into an object file
$(OUTPUT_DIR)/reading.o: reading.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile euclidean_distance.cpp into an object file
$(OUTPUT_DIR)/euclidean_distance.o: $(MODULES_DIR)/euclidean_distance.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile greedysearch.cpp into an object file
$(OUTPUT_DIR)/greedysearch.o: $(MODULES_DIR)/greedysearch.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
# Ensure the output directory exists
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Target to run tests
test: $(OUTPUT_DIR)/test
	/test

clean:
	rm -f $(OUTPUT_DIR)/euclidean_distance.o $(OUTPUT_DIR)/graph_creation.o $(OUTPUT_DIR)/reading.o $(OUTPUT_DIR)/greedysearch.o  $(OUTPUT_DIR)/main
