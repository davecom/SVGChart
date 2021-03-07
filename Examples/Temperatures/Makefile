CC = cl
FLAGS = /std:c++17 /WX /EHsc

temperatures: PPlot.obj SVGPainter.obj temperatures.obj
	$(CC) /Fe"temperatures" PPlot.obj SVGPainter.obj temperatures.obj

PPlot.obj: ..\../PPlot.cpp ..\..\PPlot.h
	$(CC) $(FLAGS) /c ..\..\PPlot.cpp

SVGPainter.obj: ..\..\SVGPainter.cpp ..\..\SVGPainter.h
	$(CC) $(FLAGS) /c ..\..\SVGPainter.cpp

temperatures.obj: temperatures.cpp
	$(CC) $(FLAGS) /I ..\..\ /c temperatures.cpp

clean:
	del temperatures.exe *.obj
