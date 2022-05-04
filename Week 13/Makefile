pa15: pa15.o
	$(CXX) $(CXXFLAGS) pa15.o -o pa15

pa15.o: pa15.cpp
	$(CXX) $(CXXFLAGS) pa15.cpp -c

clean:
	rm -f pa15 pa15.o
	
turnin:
	turnin -c cs202 -p pa15 -v recrusive.hpp pa15.cpp Makefile