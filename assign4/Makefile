all: proj4.o passserver.o
	g++ -std=c++11 proj4.cpp passserver.cpp -o proj4.mine.x -lcrypt

proj4.o:
	g++ -std=c++11 -c proj4.cpp

passserver.o:
	g++ -std=c++11 -c passserver.cpp

