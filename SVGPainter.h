//
//  SVGPainter.h
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

#ifndef SVGPainter_h
#define SVGPainter_h

#include <string>
#include <sstream>
#include "PPlot.h"

namespace SVGChart {
    using namespace std;
    
    class SVGPainter: public Painter {
    public:
        SVGPainter(long width, long height);
        // Overidden member functions
        virtual void DrawLine (float inX1, float inY1, float inX2, float inY2);
        virtual void FillRect (int inX, int inY, int inW, int inH);
        virtual void InvertRect (int inX, int inY, int inW, int inH);
        virtual void SetClipRect (int inX, int inY, int inW, int inH);
        virtual long GetWidth () const { return _width; }
        virtual long GetHeight () const { return _height; }
        virtual void SetLineColor (int inR, int inG, int inB) {
            lineRed = inR; lineGreen = inG; lineBlue = inB;
        }
        virtual void SetFillColor (int inR, int inG, int inB) {
            fillRed = inR; fillGreen = inG; fillBlue = inB;
        }
        virtual long CalculateTextDrawSize (const char *inString);
        virtual long GetFontHeight () const { return fontSize; }
        virtual void DrawText (int inX, int inY, const char *inString);
        virtual void DrawRotatedText (int inX, int inY, float inDegrees, const char *inString);
        virtual void SetStyle ([[maybe_unused]] const PStyle &inStyle){};
        void writeFile(string filePath);
        // public member variables
        
    private:
        // private member variables
        int lineRed = 0, lineGreen = 0, lineBlue = 0, fillRed = 0, fillGreen = 0, fillBlue = 0;
        int fontSize = 16;
        stringstream svgContent;
        long _width;
        long _height;
        
    };
    
}


#endif /* SVGPainter_h */
