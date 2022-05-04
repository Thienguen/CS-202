pa18: pa18.o
	$(CXX) $(CXXFLAGS) pa18.o -o pa18

pa18.o: pa18.cpp Stack.hpp
	$(CXX) $(CXXFLAGS) pa18.cpp Stack.hpp -c

clean:
	rm -f pa18 pa18.o
turnin:
	turnin -c cs202 -p pa18 -v List.hpp Stack.hpp pa18.cpp Makefile