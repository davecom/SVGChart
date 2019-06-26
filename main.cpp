//
//  main.cpp
//  
//  The main file for assignment 1; tests the data processing by producing
//  some charts.
//
//  Copyright 2019 David Kopec
//

#include "PPlot.h"
#include "SVGPainter.h"
#include <string>

using namespace std;
using namespace SVGChart;

int main() {
    PPlot pplot;
    MakePainterTester(pplot);
    SVGPainter painter(300, 300);
    pplot.Draw(painter);
    painter.writeFile("test.svg");
    
    for (int i = 1; i <= 8; i++) {
        PPlot pplot;
        MakeExamplePlot(i, pplot);
        SVGPainter painter(300, 300);
        pplot.Draw(painter);
        painter.writeFile("ExamplePlot" + to_string(i) + ".svg");
    }
    
    return 0;
}
