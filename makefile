CXX = g++
CXXFLAGS = -Wall -Iheader_files  # Add the include path for header files
OUTPUT_DIR = output

.PHONY: all clean

# Object files
OBJS = $(OUTPUT_DIR)/graph_creation.o $(OUTPUT_DIR)/reading.o

all: $(OUTPUT_DIR)/greedysearch

# Compile and link greedysearch, using the object files
$(OUTPUT_DIR)/greedysearch: greedysearch.cpp $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(OBJS)

# Compile graph_creation.cpp into an object file
$(OUTPUT_DIR)/graph_creation.o: graph_creation.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile reading.cpp into an object file
$(OUTPUT_DIR)/reading.o: reading.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Ensure the output directory exists
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

clean:
	rm -rf $(OUTPUT_DIR) greedysearch
