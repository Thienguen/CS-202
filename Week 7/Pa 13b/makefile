
pa13b-test: pa13b-test.o
	$(CXX) $(CXXFLAGS) pa13b-test.o -o pa13b-test

pa13b-test.o: pa13b-test.cxx Container.hpp
	$(CXX) $(CXXFLAGS) pa13b-test.cxx -c

clean:
	rm -f pa13b pa13b-test.o 

turnin:	
	turnin -c cs202 -p pa13b -v Container.hpp pa13b-test.cxx Makefile

