CXX = g++
CXXFLAGS = -O3 -std=c++17 -Iheader_files -pthread
OUTPUT_DIR = output
MODULES_DIR = modules

.PHONY: all clean run

OBJS = $(OUTPUT_DIR)/reading.o \
       $(OUTPUT_DIR)/medoid.o \
       $(OUTPUT_DIR)/euclidean_distance.o \
	   $(OUTPUT_DIR)/graph_creation.o \
       $(OUTPUT_DIR)/greedysearch.o \
       $(OUTPUT_DIR)/robust_ext.o \
       $(OUTPUT_DIR)/vamana.o \
       $(OUTPUT_DIR)/for_binary.o \
       $(OUTPUT_DIR)/FilteredGreedySearch.o \
       $(OUTPUT_DIR)/FilteredRobustPrune.o \
       $(OUTPUT_DIR)/FilteredVamana.o \
       $(OUTPUT_DIR)/StitchedVamana.o

all: $(OUTPUT_DIR)/main

$(OUTPUT_DIR)/main: $(MODULES_DIR)/main.cpp $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^  

$(OUTPUT_DIR)/graph_creation.o: $(MODULES_DIR)/graph_creation.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/reading.o: $(MODULES_DIR)/reading.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/medoid.o: $(MODULES_DIR)/medoid.cpp | $(OUTPUT_DIR)
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

$(OUTPUT_DIR)/FilteredGreedySearch.o: $(MODULES_DIR)/FilteredGreedySearch.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/FilteredRobustPrune.o: $(MODULES_DIR)/FilteredRobustPrune.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/FilteredVamana.o: $(MODULES_DIR)/FilteredVamana.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/StitchedVamana.o: $(MODULES_DIR)/StitchedVamana.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(OUTPUT_DIR)/main

run: $(OUTPUT_DIR)/main
	./$(OUTPUT_DIR)/main
