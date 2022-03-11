.PHONY = all clean

CXX = g++
CXXFLAGS = -g3 -std=c++17
OPTIMISE_CXX_FLAGS = -O3
 
FAST_FILES = kernels/shared.cpp kernels/k1/kernel_1_base.cpp kernels/k2/kernel_2_base.cpp kernels/k3/out-code.cpp kernels/swe1/swe_1_base.cpp kernels/swe2/swe.g.cpp kernels/euler3d1/euler3d_1_base.cpp
SLOW_FILES = data/data_generator.cpp main.cpp kernels/kernel_base.cpp

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
	${CXX} ${CXXFLAGS} ${OPTIMISE_CXX_FLAGS} -c -o $@ $<

$(SLOW_OBJ): %.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

clean:
	@echo "Cleaning up..."
	rm $(ALL_OBJECTS)
	rm KernelCompare