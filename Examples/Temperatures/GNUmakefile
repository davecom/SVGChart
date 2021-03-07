CC = g++
VPATH = ../../
FLAGS = -std=c++17 -Wall -Werror -Wextra -Wpedantic

temperatures: PPlot.o SVGPainter.o temperatures.o
	$(CC) PPlot.o SVGPainter.o temperatures.o -o temperatures

PPlot.o: ../../PPlot.cpp ../../PPlot.h
	$(CC) $(FLAGS) -c ../../PPlot.cpp

SVGPainter.o: ../../SVGPainter.cpp ../../SVGPainter.h
	$(CC) $(FLAGS) -c ../../SVGPainter.cpp

temperatures.o: temperatures.cpp
	$(CC) $(FLAGS) -I ../../ -c temperatures.cpp

clean:
	rm temperatures *.o
