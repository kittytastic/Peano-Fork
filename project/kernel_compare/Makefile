.PHONY = all clean

CXX = g++
CXX_FLAGS = -g
OPTIMISE_CXX_FLAGS = -Ofast
 
FAST_FILES = kernel_1.cpp kernel_2.cpp
SLOW_FILES = data_generator.cpp main.cpp

FAST_OBJ := $(FAST_FILES:%.cpp=%.o)
SLOW_OBJ := $(SLOW_FILES:%.cpp=%.o)
ALL_OBJECTS := $(FAST_OBJ) $(SLOW_OBJ)

all: $(ALL_OBJECTS)
	@echo "Target objects: $(ALL_OBJECTS)"
	@echo "Fast objects: $(FAST_FILES)"
	@echo "Normal objects: $(SLOW_FILES)\n"
	${CXX} -lm $(ALL_OBJECTS) -o KernelCompare


$(FAST_OBJ): %.o: %.cpp
	${CXX} ${CXX_FLAGS} ${OPTIMISE_CXX_FLAGS} -c $<

$(SLOW_OBJ): %.o: %.cpp
	${CXX} ${CXX_FLAGS} -c $<

clean:
	@echo "Cleaning up..."
	rm KernelCompare
	rm *.o