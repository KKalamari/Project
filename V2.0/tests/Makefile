CXX = g++
CXXFLAGS =  -g 

# target executable names
MEDOID_TARGET = medoid_test
FILTERED_GREEDY_TARGET=FilteredGreedyTest
FILTERED_ROBUST_TARGET=FilteredRobustTest
FILTERED_VAMANA_TARGET=FilteredVamanaTest

# Acutest include directory
MEDOID_SRCS = medoid_test.cpp ./../modules/medoid.cpp
FILTERED_SRCS = FilteredGreedyTest.cpp ./../modules/FilteredGreedySearch.cpp ./../modules/euclidean_distance.cpp
FILTERED_ROBUST_SRCS = FilteredRobustTest.cpp ./../modules/FilteredRobustPrune.cpp ./../modules/euclidean_distance.cpp ./../modules/FilteredGreedySearch.cpp
FILTERED_VAMANA_SRCS = FilteredVamanaTest.cpp ./../modules/medoid.cpp ./../modules/euclidean_distance.cpp ./../modules/FilteredVamana.cpp ./../modules/FilteredRobustPrune.cpp ./../modules/FilteredGreedySearch.cpp


# Acutest include directory
ACUTEST_DIR = ./../header_files  #path to the directory with header files
ACUTEST_FLAGS = -I$(ACUTEST_DIR)  #include Acutest header
MEDOID_DIR=./../header_files


#the target rule to build the executables
all: $(MEDOID_TARGET) $(FILTERED_GREEDY_TARGET) $(FILTERED_ROBUST_TARGET) $(FILTERED_VAMANA_TARGET)

$(MEDOID_TARGET): $(MEDOID_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(MEDOID_DIR) -o $(MEDOID_TARGET) $(MEDOID_SRCS)

$(FILTERED_GREEDY_TARGET): $(FILTERED_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(MEDOID_DIR) -o $(FILTERED_GREEDY_TARGET) $(FILTERED_SRCS)

$(FILTERED_ROBUST_TARGET): $(FILTERED_ROBUST_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(MEDOID_DIR) -o $(FILTERED_ROBUST_TARGET) $(FILTERED_ROBUST_SRCS)

$(FILTERED_VAMANA_TARGET): $(FILTERED_VAMANA_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(MEDOID_DIR) -o $(FILTERED_VAMANA_TARGET) $(FILTERED_VAMANA_SRCS)

clean:
	rm -f $(MEDOID_TARGET) $(FILTERED_GREEDY_TARGET) $(FILTERED_ROBUST_TARGET) $(FILTERED_VAMANA_TARGET)

run: $(MEDOID_TARGET)
	./$(MEDOID_TARGET)
	./$(FILTERED_ROBUST_TARGET)
	./$(FILTERED_GREEDY_TARGET)
	./$(FILTERED_VAMANA_TARGET)
