//
//  SVGPainter.cpp
//  
//  A PPlot Painter Subclass for drawing a
//  chart to an SVG file.
//
//  Copyright 2019 David Kopec
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

#include "SVGPainter.h"
#include <cstring>
#include <fstream>

namespace SVGChart {
    using namespace std;
    
    SVGPainter::SVGPainter(long width, long height):  _width(width), _height(height) {
        svgContent << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
        svgContent << "<svg version=\"1.1\" baseProfile=\"full\" width=\"";
        svgContent << to_string(width);
        svgContent << "\" height=\"";
        svgContent << to_string(height);
        svgContent << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    }
    
    void SVGPainter::DrawLine (float inX1, float inY1, float inX2, float inY2) {
        svgContent << "<line x1=\"" << inX1 << "\" y1=\"" << inY1;
        svgContent << "\" x2=\"" << inX2 << "\" y2=\"" << inY2;
        svgContent << "\" stroke=\"" << "rgb(" << lineRed << ",";
        svgContent << lineGreen << "," << lineBlue << ")" << "\" />\n";
    }
    
    void SVGPainter::FillRect (int inX, int inY, int inW, int inH) {
        svgContent << "<rect x=\"" << inX << "\" y=\"" << inY;
        svgContent << "\" width=\"" << inW << "\" height=\"" << inH;
        svgContent << "\" fill=\"" << "rgb(" << fillRed << ",";
        svgContent << fillGreen << "," << fillBlue << ")" << "\" />\n";
    }
    
    void SVGPainter::InvertRect (int inX, int inY, int inW, int inH) {
        svgContent << "<rect x=\"" << inX << "\" y=\"" << inY;
        svgContent << "\" width=\"" << inW << "\" height=\"" << inH;
        svgContent << "\" fill=\"" << "rgba(" << fillRed << ",";
        svgContent << fillGreen << "," << fillBlue << "," << 0.2;
        svgContent << ")" << "\" />\n";
    }
    
    void SVGPainter::SetClipRect (int inX, int inY, int inW, int inH) {
        svgContent << "<clipPath>\n";
        FillRect(inX, inY, inW, inH);
        svgContent << "</clipPath>\n";
    }
    
    // The following array & function snippet are translated to C++ from this source
    // https://stackoverflow.com/a/42816496/281461
    const int LCARS_CHAR_SIZE_ARRAY[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 26, 46, 63, 42, 105, 45, 20, 25, 25, 47, 39, 21, 34, 26, 36, 36, 28, 36, 36, 36, 36, 36, 36, 36, 36, 27, 27, 36, 35, 36, 35, 65, 42, 43, 42, 44, 35, 34, 43, 46, 25, 39, 40, 31, 59, 47, 43, 41, 43, 44, 39, 28, 44, 43, 65, 37, 39, 34, 37, 42, 37, 50, 37, 32, 43, 43, 39, 43, 40, 30, 42, 45, 23, 25, 39, 23, 67, 45, 41, 43, 42, 30, 40, 28, 45, 33, 52, 33, 36, 31, 39, 26, 39, 55};
    
    long SVGPainter::CalculateTextDrawSize (const char *inString) {
        float width = 0;
        float scaleFactor = fontSize / 100.0;;
        
        auto length = strlen(inString);
        for (unsigned long i = 0; i < length; i++) {
            if (inString[i] > 126) {
                width += 65; // default increase for unknown characters
            }
            width = width + LCARS_CHAR_SIZE_ARRAY[(int)inString[i]];
        }
        float padding = 25.0; // 25 is a little bit of padding
        return long(width * scaleFactor + padding);
    }
    
    void SVGPainter::DrawText (int inX, int inY, const char *inString) {
        svgContent << "<text x=\"" << inX << "\" y=\"" << inY;
        svgContent << "\" fill=\"" << "rgb(" << lineRed << ",";
        svgContent << lineGreen << "," << lineBlue << ")" << "\">\n";
        svgContent << inString << "</text>\n";
    }
    
    void SVGPainter::DrawRotatedText (int inX, int inY, float inDegrees, const char *inString) {
        svgContent << "<text x=\"" << inX << "\" y=\"" << inY << "\" transform=";
        svgContent << "\"rotate(" << inDegrees;
        svgContent << "," << inX << "," << inY << ")\">";
        svgContent << inString << "</text>\n";
    }

    void SVGPainter::writeFile(string filePath) {
        ofstream outFile;
        outFile.open(filePath);
        outFile << svgContent.rdbuf();
        outFile << "</svg>\n" << endl;
        outFile.close();
    }
}
