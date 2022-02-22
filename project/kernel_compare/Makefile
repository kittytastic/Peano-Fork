.PHONY = all clean

CXX = g++
CXXFLAGS = -g3
OPTIMISE_CXX_FLAGS = -Ofast
 
FAST_FILES = kernel_1.cpp kernel_2_base.cpp
SLOW_FILES = data_generator.cpp main.cpp

FAST_OBJ := $(FAST_FILES:%.cpp=%.o)
SLOW_OBJ := $(SLOW_FILES:%.cpp=%.o)
ALL_OBJECTS := $(FAST_OBJ) $(SLOW_OBJ)

# Link to ExaHyPE libs
CXXFLAGS += -I. -I../../src -DPeanoDebug=0
LDFLAGS  += -L../../src  -L../../src/toolbox/loadbalancing  -L../../src/toolbox/blockstructured  -L../../src/exahype2
LIBS +=  -lExaHyPE2Core2d -lToolboxBlockstructured2d -lToolboxLoadBalancing2d -lPeano4Core2d -lTarch

all: $(ALL_OBJECTS)
	@echo "Target objects: $(ALL_OBJECTS)"
	@echo "Fast objects: $(FAST_FILES)"
	@echo "Normal objects: $(SLOW_FILES)\n"
	${CXX} $(ALL_OBJECTS) $(LDFLAGS) $(LIBS)  -o KernelCompare


$(FAST_OBJ): %.o: %.cpp
	${CXX} ${CXXFLAGS} ${OPTIMISE_CXX_FLAGS} -c $<

$(SLOW_OBJ): %.o: %.cpp
	${CXX} ${CXXFLAGS} -c $<

clean:
	@echo "Cleaning up..."
	rm KernelCompare
	rm *.o