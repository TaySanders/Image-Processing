//
// Created by Taylor Sanders on 3/21/22.
//

#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>


using namespace std;
#ifndef PROJECT_2_HEAD_H
#define PROJECT_2_HEAD_H


class Image {

    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    struct Pixel {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };

public:
    vector <Pixel> pixels;
    Header header;
    int totalPixels;

    void readFileHeader(const string& filename);

    void writeToFile(const string& filename);

    Image Multiply(Image& imageOne, Image& imageTwo);

    Image Subtract(Image& imageOne, Image& imageTwo);

    Image Screen(Image& imageOne, Image& imageTwo);

    Image Overlay(Image& imageOne, Image& imageTwo);

    Image AddGreen(Image& imageOne);

    Image scaleRedBlue(Image& imageOne);

    Image seperateRed(Image& imageOne) const;

    Image seperateGreen(Image& imageOne) const;

    Image seperateBlue(Image& imageOne) const;

    Image combineLayers(Image& imageOne, Image& imageTwo, Image& imageThree);

    Image Rotate(Image& imageOne);

    int TestAll(Image& imageOne, Image& imageTwo, int count);

};





#endif //PROJECT_2_HEAD_H
