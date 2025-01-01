CXX = g++
CXXFLAGS = -O3  -Iheader_files 
OUTPUT_DIR = output
MODULES_DIR = modules

.PHONY: all clean run valgrind

OBJS = $(OUTPUT_DIR)/reading.o \
	   $(OUTPUT_DIR)/medoid.o \
	   $(OUTPUT_DIR)/euclidean_distance.o \
	   $(OUTPUT_DIR)/FilteredGreedySearch.o \
	   $(OUTPUT_DIR)/FilteredRobustPrune.o \
	   $(OUTPUT_DIR)/FilteredVamana.o  \
	   $(OUTPUT_DIR)/groundtruth.o \
	   $(OUTPUT_DIR)/Vamana.o \
	   $(OUTPUT_DIR)/GreedySearch.o \
	   $(OUTPUT_DIR)/Robust_ext.o \
	   $(OUTPUT_DIR)/Stitched.o \
	   $(OUTPUT_DIR)/for_binary.o \
	   $(OUTPUT_DIR)/reading_groundtruth.o

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

$(OUTPUT_DIR)/Vamana.o: $(MODULES_DIR)/Vamana.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/GreedySearch.o: $(MODULES_DIR)/GreedySearch.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/Robust_ext.o: $(MODULES_DIR)/Robust_ext.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/Stitched.o: $(MODULES_DIR)/Stitched.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/for_binary.o: $(MODULES_DIR)/for_binary.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/reading_groundtruth.o: $(MODULES_DIR)/reading_groundtruth.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

clean:
	rm -f $(OBJS) $(OUTPUT_DIR)/main

run: $(OUTPUT_DIR)/main
	./$(OUTPUT_DIR)/main
