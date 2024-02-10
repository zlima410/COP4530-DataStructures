all: test_list.o
	g++ -std=c++11 test_list.o -o list
test_list.o: test_list.cpp
	g++ -std=c++11 -c test_list.cpp
clean:
	rm -rf test_list.o list