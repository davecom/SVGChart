//
//  temperatures.cpp
//  
//  Draws a line chart of average temperatures in two cities.
//
//  Copyright 2021 David Kopec
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation files
//  (the "Software"), to deal in the Software without restriction,
//  including without limitation the rights to use, copy, modify, merge,
//  publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice
//  shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.

#include "PPlot.h"
#include "SVGPainter.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
using namespace SVGChart;

// Remove extraneous characters from string so it can
// be converted into a number
void clean(string &str) {
    string unwanted = "\"\' \t\n";
    str.erase(remove_if(str.begin(), str.end(), [&](char &c){
        return !unwanted.find_first_of(c);
    }));
}

// Read from a input string stream we hit the next comma, or the end
// and try to convert it into the float we seek.
float readFloatCell(istringstream &iss) {
    string holder;
    getline(iss, holder, ',');
    clean(holder);
    return stof(holder);
}

// Read from a input string stream we hit the next comma, or the end
// and try to convert it into the int we seek.
int readIntCell(istringstream &iss) {
    string holder;
    getline(iss, holder, ',');
    clean(holder);
    return stoi(holder);
}

// Read from a input string stream we hit the next comma, or the end
// and try to convert it into the string we seek.
string readStringCell(istringstream &iss) {
    string holder;
    getline(iss, holder, ',');
    return holder;
}

// Read a single line from a file stream and turn it into a CityYear
float readTemperatureFromLine(ifstream &file) {
    string holder;
    getline(file, holder); //test the read for success
    istringstream line(holder);
    readStringCell(line); // discard station
    readStringCell(line); // discard name
    readIntCell(line); // discard year
    readIntCell(line); // discard days below 32
    readIntCell(line); // discard days above 90
    float avgTemp = readFloatCell(line);
    readFloatCell(line); // discard average max
    readFloatCell(line); // discard average min
    return avgTemp;
}

// Read city by looking at the specified lines in the CSV
float *readCityTemperatures(string fileName, int startLine, int endLine)  {
    ifstream file(fileName);
    int curLine = 0;
    const int numYears = (endLine - startLine) + 1;
    float *data = new float[numYears];
    while (file.good() && curLine <= endLine) {
        if (curLine >= startLine) {
            data[curLine - startLine] = readTemperatureFromLine(file);
        } else { // disposable line
            string throwaway;
            getline(file, throwaway);
        }
        curLine++;
    }
    file.close();
    return data;
}

// Draw a chart showing the average temperatures
// for each city in "AvgTempChart.svg"
static void drawAvgTempChart(string city1Name, string city2Name, int startYear, int numYears, float *city1Data, float *city2Data) {
    PPlot pplot;
    pplot.mPlotBackground.mTitle = "Average Temperature";
    PlotData *theX1 = new PlotData ();
    PlotData *theY1 = new PlotData ();
    for (int i = startYear; i < startYear + numYears; i++) {
        theX1->push_back (i);
        theY1->push_back (city1Data[i - startYear]);
    }
    LineDataDrawer *theDataDrawer1 = new LineDataDrawer ();
    theDataDrawer1->mDrawPoint = false;
    theDataDrawer1->mDrawLine = true;
    
    LegendData *legend1 = new LegendData ();// let us setup the first legend
    legend1->mName = city1Name;
    legend1->mColor = PColor (100,0,200);// just an rgb value
    
    pplot.mPlotDataContainer.AddXYPlot (theX1, theY1, legend1, theDataDrawer1);
    
    PlotData *theX2 = new PlotData ();
    PlotData *theY2 = new PlotData ();
    for (int i = startYear; i < startYear + numYears; i++) {
        theX2->push_back (i);
        theY2->push_back (city2Data[i - startYear]);
    }
    LineDataDrawer *theDataDrawer2 = new LineDataDrawer ();
    theDataDrawer2->mDrawPoint = false;
    theDataDrawer2->mDrawLine = true;
    
    LegendData *legend2 = new LegendData ();// let us setup the first legend
    legend2->mName = city2Name;
    legend2->mColor = PColor (100,200,200);// just an rgb value
    
    pplot.mPlotDataContainer.AddXYPlot (theX2, theY2, legend2, theDataDrawer2);
    
    pplot.mMargins.mLeft = 100;
    pplot.mMargins.mTop = 50;
    pplot.mMargins.mRight = 50;
    pplot.mMargins.mBottom = 50;
    pplot.mGridInfo.mXGridOn = true;
    pplot.mGridInfo.mYGridOn = true;
    pplot.mYAxisSetup.mCrossOrigin = false;
    pplot.mXAxisSetup.mCrossOrigin = false;
    pplot.mXAxisSetup.mLabel = "Year";
    pplot.mYAxisSetup.mAutoScaleMin = false;
    pplot.mYAxisSetup.mAutoScaleMax = false;
    pplot.mYAxisSetup.mMin = 0;
    pplot.mYAxisSetup.mMax = 100;
    pplot.mYAxisSetup.mLabel = "Temperature (F)";
    SVGPainter painter(800, 600);
    pplot.Draw(painter);
    painter.writeFile("AvgTempChart.svg");
}

// Test all code and draw charts.
int main() {
    // draw graphs
    float *nycData = readCityTemperatures("tempdata.csv", 1, 51);
    float *burlingtonData = readCityTemperatures("tempdata.csv", 52, 102);
    drawAvgTempChart("NYC, NY", "Burlington, VT", 1968, 51, nycData, burlingtonData);
    delete[] nycData;
    delete[] burlingtonData;
    return 0;
}

