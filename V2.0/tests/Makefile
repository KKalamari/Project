CXX = g++
CXXFLAGS = -g -mavx -mavx2 -mfma




MEDOID_TARGET = medoid_test
FILTERED_GREEDY_TARGET = FilteredGreedyTest
FILTERED_ROBUST_TARGET = FilteredRobustTest
FILTERED_VAMANA_TARGET = FilteredVamanaTest

MEDOID_SRCS = medoid_test.cpp ./../modules/medoid.cpp
FILTERED_SRCS = FilteredGreedyTest.cpp ./../modules/FilteredGreedySearch.cpp ./../modules/Euclidean_distance.cpp
FILTERED_ROBUST_SRCS = FilteredRobustTest.cpp ./../modules/FilteredRobustPrune.cpp ./../modules/Euclidean_distance.cpp ./../modules/FilteredGreedySearch.cpp
FILTERED_VAMANA_SRCS = FilteredVamanaTest.cpp ./../modules/medoid.cpp ./../modules/Euclidean_distance.cpp ./../modules/FilteredVamana.cpp ./../modules/FilteredRobustPrune.cpp ./../modules/FilteredGreedySearch.cpp ./../modules/Stitched.cpp ./../modules/Vamana.cpp ./../modules/GreedySearch.cpp ./../modules/Robust_ext.cpp

ACUTEST_DIR = ./../header_files  
ACUTEST_FLAGS = -I$(ACUTEST_DIR)  
MEDOID_DIR = ./../header_files

FOR_BINARY_SRCS = ./../modules/for_binary.cpp  

all: $(MEDOID_TARGET) $(FILTERED_GREEDY_TARGET) $(FILTERED_ROBUST_TARGET) $(FILTERED_VAMANA_TARGET)

$(MEDOID_TARGET): $(MEDOID_SRCS) $(FOR_BINARY_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(MEDOID_DIR) -o $(MEDOID_TARGET) $(MEDOID_SRCS) $(FOR_BINARY_SRCS)

$(FILTERED_GREEDY_TARGET): $(FILTERED_SRCS) $(FOR_BINARY_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(MEDOID_DIR) -o $(FILTERED_GREEDY_TARGET) $(FILTERED_SRCS) $(FOR_BINARY_SRCS)

$(FILTERED_ROBUST_TARGET): $(FILTERED_ROBUST_SRCS) $(FOR_BINARY_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(MEDOID_DIR) -o $(FILTERED_ROBUST_TARGET) $(FILTERED_ROBUST_SRCS) $(FOR_BINARY_SRCS)

$(FILTERED_VAMANA_TARGET): $(FILTERED_VAMANA_SRCS) $(FOR_BINARY_SRCS)
	$(CXX) $(CXXFLAGS) $(ACUTEST_FLAGS) -I$(MEDOID_DIR) -o $(FILTERED_VAMANA_TARGET) $(FILTERED_VAMANA_SRCS) $(FOR_BINARY_SRCS)

clean:
	rm -f $(MEDOID_TARGET) $(FILTERED_GREEDY_TARGET) $(FILTERED_ROBUST_TARGET) $(FILTERED_VAMANA_TARGET)

run: $(MEDOID_TARGET) $(FILTERED_GREEDY_TARGET) $(FILTERED_ROBUST_TARGET) $(FILTERED_VAMANA_TARGET)
	./$(MEDOID_TARGET)
	./$(FILTERED_ROBUST_TARGET)
	./$(FILTERED_GREEDY_TARGET)
	./$(FILTERED_VAMANA_TARGET)

valgrind: $(MEDOID_TARGET) $(FILTERED_GREEDY_TARGET) $(FILTERED_ROBUST_TARGET) $(FILTERED_VAMANA_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(MEDOID_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(FILTERED_ROBUST_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(FILTERED_GREEDY_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(FILTERED_VAMANA_TARGET)
