CC = g++
FLAGS = -std=c++17 -Wall -Werror -Wextra -Wpedantic

test: PPlot.o SVGPainter.o main.o
	$(CC) PPlot.o SVGPainter.o main.o -o test

PPlot.o: PPlot.cpp PPlot.h
	$(CC) $(FLAGS) -c PPlot.cpp

SVGPainter.o: SVGPainter.cpp SVGPainter.h
	$(CC) $(FLAGS) -c SVGPainter.cpp

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

clean:
	rm test *.o
