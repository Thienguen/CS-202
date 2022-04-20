pa17b: pa17b.o
	$(CXX) $(CXXFLAGS) pa17b.o -o pa17b

pa17b.o: pa17b.cpp List.hpp 
	$(CXX) $(CXXFLAGS) pa17b.cpp List.hpp -c 

pa17b_test: pa17b_test.o
	$(CXX) $(CXXFLAGS) pa17b_test.o -o pa17b_test

pa17b_test.o: pa17b_test.cpp List.hpp
	$(CXX) $(CXXFLAGS) pa17b_test.cpp List.hpp -c

pa17b_wordcount: pa17b_wordcount.o
	$(CXX) $(CXXFLAGS) pa17b_wordcount.o -o pa17b_wordcount

pa17b_wordcount.o: pa17b_wordcount.cpp List.hpp
	$(CXX) $(CXXFLAGS) pa17b_wordcount.cpp List.hpp -c

clean:
	rm -f pa17b pa17b.o
	rm -f List_test List_test.o
	rm -f pa17b_wordcount pa17b_wordcount.o

turnin:
	turnin -c cs202 -p pa17b -v \
	List.hpp pa17b.cpp Makefile \
	pa17b-wordcount.cpp List_test.cpp List_2.hpp