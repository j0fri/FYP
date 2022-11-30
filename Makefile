default: sim

CXX = g++
CXXFLAGS = -Wall -O0

SIMHDRS = Simulation.h Species.h Field.o
SIMOBJS = sim.o Simulation.o Species.o Field.o
SIMLIBS = -lboost_program_options -lblas -llapack

VISHDRS = 
VISOBJS = vis.o
VISLIBS = 

HDRS = $(SIMHDRS) $(VISHDRS)
OBJS = $(SIMOBJS) $(VISOBJS)

%.o : %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

sim: $(SIMOBJS)
	$(CXX) -o $@ $^ $(SIMLIBS)

vis: $(VISOBJS)
	$(CXX) -o $@ $^ $(VISLIBS)

.PHONY: clean
clean:
	-rm -f *.o sim vis

