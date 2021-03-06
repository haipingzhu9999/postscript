#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include "postscript.hh"
using namespace std;

void Postscript::line(int a, int b, int c, int d){
    char buffer[256];
    int size = sprintf(buffer, "%d %d moveto %d %d lineto stroke\n", a, b, c, d);
    s.write(buffer, size);
}

void Postscript::setStrokeColor(int r, int g, int b){
    float red, green, blue;
    char buffer[256];
    
    red = r / 255.0;
    green = g / 255.0;
    blue= b / 255.0;
    
    sprintf(buffer, "%f %f %f setrgbcolor\n", red, green, blue);
    strcpy(strokeColor, buffer);
}

void Postscript::setFillColor(int r, int g, int b){
    float red, green, blue;
    char buffer[256];
    
    red = r / 255.0;
    green = g / 255.0;
    blue= b / 255.0;
    
    sprintf(buffer, "%f %f %f setrgbcolor\n", red, green, blue);
    strcpy(fillColor, buffer);
}

void Postscript::drawRect(float x, float y, float w, float h){
    char buffer[256];
    int size = sprintf(buffer, "%f %f moveto %f %f lineto %f %f lineto %f %f lineto closepath\n%sstroke\n", x, y, x+w, y, x+w, y+h, x, y+h, strokeColor);
    s.write(buffer, size);
}

void Postscript::fillRect(float x, float y, float w, float h){
    char buffer[256];
    int size = sprintf(buffer, "%f %f moveto %f %f lineto %f %f lineto %f %f lineto closepath\n%sfill\n", x, y, x+w, y, x+w, y+h, x, y+h, fillColor);
    s.write(buffer, size);
}

void Postscript::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3){
    char buffer[256];
    int size = sprintf(buffer, "%f %f moveto %f %f lineto %f %f lineto closepath\n%sstroke\n", x1, y1, x2, y2, x3, y3, strokeColor);
    s.write(buffer, size);
}

void Postscript::fillTriangle(float x1, float y1, float x2, float y2, float x3, float y3){
    char buffer[256];
    int size = sprintf(buffer, "%f %f moveto %f %f lineto %f %f lineto closepath\n%sfill\n", x1, y1, x2, y2, x3, y3, fillColor);
    s.write(buffer, size);
}

void Postscript::drawCircle(float x, float y, float r){
    char buffer[256];
    int size = sprintf(buffer, "%f %f %f 0 360 arc\n%sstroke\n", x, y, r, strokeColor);
    s.write(buffer, size);
}

void Postscript::fillCircle(float x, float y, float r){
    char buffer[256];
    int size = sprintf(buffer, "%f %f %f 0 360 arc\n%sfill\n", x, y, r, fillColor);
    s.write(buffer, size);
}

void Postscript::text(float x, float y, const char* str){
    unsigned int len = strlen(str);
    char buffer[256 + len];
    int size = sprintf(buffer, "/Times-Roman findfont 12 scalefont setfont newpath %f %f moveto (%s) %sshow\n", x, y, str, strokeColor);
    s.write(buffer, size);
}

void Postscript::grid(float x1, float interval_x, float x2, float y1, float interval_y, float y2){
    char buffer1[256];
    char buffer2[256];
    char buffer3[256];
    char buffer4[256];
    
    int bins_x = int((x2 - x1) / interval_x);
    int bins_y =int((y2 - y1) / interval_y);
    
    int size1 = sprintf(buffer1, "/vline {%f %f moveto %f %f lineto stroke} def\n", x1, y1, x1, y2);
    s.write(buffer1, size1);
    int size2 = sprintf(buffer2, "gsave\nvline\n%d {%f 0 translate vline} repeat\ngrestore\n", bins_x, interval_x);
    s.write(buffer2, size2);
    
    int size3 = sprintf(buffer3, "/hline {%f %f moveto %f %f lineto stroke} def\n", x1, y1, x2, y1);
    s.write(buffer3, size3);
    int size4 = sprintf(buffer4, "gsave\nhline\n%d {0 %f translate hline} repeat\ngrestore\n", bins_y, interval_y);
    s.write(buffer4, size4);
}