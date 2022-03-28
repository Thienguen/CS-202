
pa17a-test: pa17a-test.o
	$(CXX) $(CXXFLAGS) pa17a-test.o -o pa17a-test

pa17-test.o: simple_list_test.cpp simple_list.cpp
	$(CXX) $(CXXFLAGS) pa17a-test.cpp -c

pa17a: pa17a.o
	$(CXX) $(CXXFLAGS) pa17a.o -o pa17a

pa17a.o: pa17a.cpp simple_list.cpp
	$(CXX) $(CXXFLAGS) pa17a.cpp -c

clean: 
	rm -f pa17a pa17.o
	rm -f pa17a-test pa17a-test.o

turnin: 
	turnin —c cs202 —p pa17a —v \
	simple_list.h simple_list.cpp pa17a.cpp Makefile

