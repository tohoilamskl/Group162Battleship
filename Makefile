#Makefile

displayGameHistory.o: displayGameHistory.cpp displayGameHistory.h
	g++ -c displayGameHistory.cpp

main.o: main.cpp displayGameHistory.h
	g++ -c main.cpp

main: displayGameHistory.o main.o
	g++ displayGameHistory.o main.o -o main
