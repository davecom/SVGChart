CC = cl
FLAGS = /std:c++17 /WX /EHsc

test: PPlot.obj SVGPainter.obj main.obj
	$(CC) /Fe"test" PPlot.obj SVGPainter.obj main.obj

PPlot.obj: PPlot.cpp PPlot.h
	$(CC) $(FLAGS) /c PPlot.cpp

SVGPainter.obj: SVGPainter.cpp SVGPainter.h
	$(CC) $(FLAGS) /c SVGPainter.cpp

main.obj: main.cpp
	$(CC) $(FLAGS) /c main.cpp

clean:
	del test.exe *.obj
