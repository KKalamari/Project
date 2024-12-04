#compiler and Flags
CXX = g++
CXXFLAGS = -O3  -Iheader_files #add the include path for header files
OUTPUT_DIR = output
MODULES_DIR = modules

.PHONY: all clean run

#object files
OBJS = $(OUTPUT_DIR)/reading.o \
	   $(OUTPUT_DIR)/medoid.o \
	   $(OUTPUT_DIR)/euclidean_distance.o \
	   $(OUTPUT_DIR)/FilteredGreedySearch.o \
	   $(OUTPUT_DIR)/FilteredRobustPrune.o \
	   $(OUTPUT_DIR)/FilteredVamana.o  \
	   $(OUTPUT_DIR)/groundtruth.o
#main target
all: $(OUTPUT_DIR)/main

$(OUTPUT_DIR)/main: $(MODULES_DIR)/main.cpp $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^  

$(OUTPUT_DIR)/reading.o: $(MODULES_DIR)/reading.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/medoid.o: $(MODULES_DIR)/medoid.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/euclidean_distance.o: $(MODULES_DIR)/euclidean_distance.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/FilteredGreedySearch.o: $(MODULES_DIR)/FilteredGreedySearch.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/FilteredRobustPrune.o: $(MODULES_DIR)/FilteredRobustPrune.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/FilteredVamana.o: $(MODULES_DIR)/FilteredVamana.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/groundtruth.o: $(MODULES_DIR)/groundtruth.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<



$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

clean:
	rm -f $(OBJS) $(OUTPUT_DIR)/main

run: $(OUTPUT_DIR)/main
	./$(OUTPUT_DIR)/main