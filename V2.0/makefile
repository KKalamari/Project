#compiler and Flags
CXX = g++
CXXFLAGS = -O3  -Iheader_files #add the include path for header files
OUTPUT_DIR = output
MODULES_DIR = modules

.PHONY: all clean run

#object files
OBJS = $(OUTPUT_DIR)/reading.o \
	   $(OUTPUT_DIR)/medoid.o

#main target
all: $(OUTPUT_DIR)/main

$(OUTPUT_DIR)/main: $(MODULES_DIR)/main.cpp $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^  # Use $^ instead of $<

$(OUTPUT_DIR)/reading.o: $(MODULES_DIR)/reading.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/medoid.o: $(MODULES_DIR)/medoid.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

clean:
	rm -f $(OBJS) $(OUTPUT_DIR)/main

run: $(OUTPUT_DIR)/main
	./$(OUTPUT_DIR)/main