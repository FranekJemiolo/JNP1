CXX = g++
DEBUG_FLAGS = -Wall -O0 -std=c++11 -g -c -DDEBUG
RELEASE_FLAGS = -Wall -O2 -std=c++11 -c

all: clean strset.o strsetconst.o
strset.o: strset.cc strsetconst.h strset.h
ifeq ($(debuglevel), 1)	
	$(CXX) $(DEBUG_FLAGS) $< -o $@
else
	$(CXX) $(RELEASE_FLAGS) $< -o $@
endif
strsetconst.o: strsetconst.cc strsetconst.h strset.h
ifeq ($(debuglevel), 1)	
	$(CXX) $(DEBUG_FLAGS) $< -o $@
else
	$(CXX) $(RELEASE_FLAGS) $< -o $@
endif

clean:
	rm -f *.o
