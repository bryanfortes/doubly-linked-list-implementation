all: main.x

main.x: test_list.cpp List.hpp
	g++ test_list.cpp -o main.x -std=c++11
 
clean:
	rm *.x
	rm *.o
