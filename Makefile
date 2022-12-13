default: sim

CXX = g++
CXXFLAGS = -Wall -O5

SIMHDRS = Simulation.h Species.h Field.h math_helper.h
SIMOBJS = sim.o Simulation.o Species.o Field.o math_helper.o
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
	
#--Lx 12.56637

.PHONY: landauFile
landauFile: sim
	./sim  --mode 1