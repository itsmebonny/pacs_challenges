CXX      ?= g++


LDLIBS+=-L$(mkBoostLib) -lboost_iostreams -lboost_system -lboost_filesystem
CXXFLAGS ?= -std=c++20 $(LDLIBS)
INCLUDE_DIR = include/
CPPFLAGS ?= -O3 -Wall -I$(INCLUDE_DIR) -I$(mkBoostInc) -DGNUPLOT -w

EXEC     = main 


all: $(EXEC)

%.o: %.cpp 
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(EXEC): %: %.o
	$(CXX) $(CXXFLAGS)  $< -o $@
exec:
	./$(EXEC)
clean:
	$(RM) *.o
plot:
	gnuplot -p plot.p
distclean: clean
	$(RM) $(EXEC) $(EXEC_MUPARSER)
	$(RM) *~
