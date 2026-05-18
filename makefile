# Common compiler flags
CXXFLAGS = -g -Wall -std=c++11

# List of all your header files
HEADERS = String.h

# Common object files (excluding main*.o)
COMMON_OBJS = String.o

# Pattern rule to compile any .cpp -> .o
%.o : %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Explicit rule for the default "driver" (from main.cpp)
all: driver

driver: $(COMMON_OBJS) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Pattern rule to build main1, main2, ..., main10 executables
# This matches any target named main1, main2, ..., main10
main%: $(COMMON_OBJS) main%.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Convenience target to build all 10 mains (optional)
all-mains: main main1 main2 main3 main4 main5 main6 main7 main8 main9 main10

# Clean everything
clean:
	rm -f *.o driver main main1 main2 main3 main4 main5 main6 main7 main8 main9 main10

.PHONY: all driver all-mains clean
