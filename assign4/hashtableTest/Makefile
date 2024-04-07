all: test_hashtable.o
	g++ -std=c++11 test_hashtable.o -o hashTest

test_hashtable.o: test_hashtable.cpp
	g++ -std=c++11 -c test_hashtable.cpp

clean:
	rm -rf test_hashtable.o hashTest