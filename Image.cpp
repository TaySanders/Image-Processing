//
// Created by Taylor Sanders on 3/21/22.
//
#include "Image.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;


void Image::readFileHeader(const string& filename) {
    ifstream file;
    file.open(filename, ios_base::binary);

    if (file.is_open()) {
        //cout << "File is open" << endl;

        file.read(&header.idLength, sizeof(header.idLength));

        file.read(&header.colorMapType, sizeof(header.colorMapType));

        file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));

        file.read((char *) &header.colorMapOrigin, sizeof(header.colorMapOrigin));

        file.read((char *) &header.colorMapLength, sizeof(header.colorMapLength));

        file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));

        file.read((char *) &header.xOrigin, sizeof(header.xOrigin));

        file.read((char *) &header.yOrigin, sizeof(header.yOrigin));

        file.read((char *) &header.width, sizeof(header.width));

        file.read((char *) &header.height, sizeof(header.height));

        file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));

        file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

        totalPixels = header.height * header.width;

        for (int i = 0; i < totalPixels; i++) {
            Pixel pixel;
            unsigned char temp;
            file.read((char *) &temp, 1);
            pixel.blue = temp;
            file.read((char *) &temp, 1);
            pixel.green = temp;
            file.read((char *) &temp, 1);
            pixel.red = temp;

            pixels.push_back(pixel);
        }
    }
    else {
        cout << "File didn't opened";
    }
    file.close();
}

void Image::writeToFile(const string& filename) {
    ofstream file;
    file.open(filename);

    if (file.is_open()) {
        //cout << "File is open";

        file.write(&header.idLength, sizeof(header.idLength));

        file.write(&header.colorMapType, sizeof(header.colorMapType));

        file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));

        file.write((char *) &header.colorMapOrigin, sizeof(header.colorMapOrigin));

        file.write((char *) &header.colorMapLength, sizeof(header.colorMapLength));

        file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));

        file.write((char *) &header.xOrigin, sizeof(header.xOrigin));

        file.write((char *) &header.yOrigin, sizeof(header.yOrigin));

        file.write((char *) &header.width, sizeof(header.width));

        file.write((char *) &header.height, sizeof(header.height));

        file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));

        file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));


        for (int i = 0; i < pixels.size(); i++) {
            file.write((char *) &pixels[i].blue, 1);
            file.write((char *) &pixels[i].green, 1);
            file.write((char *) &pixels[i].red, 1);
        }
    }
    else {
        cout << "File didn't opened";
    }
    file.close();
}

Image Image::Multiply(Image& imageOne, Image& imageTwo){
    Image tempImage;
    tempImage.header = imageOne.header;
    tempImage.totalPixels = imageOne.totalPixels;

    for(unsigned int i = 0; i < imageOne.totalPixels; i++) {
        Pixel pixelTemp;
        pixelTemp.red = ((imageOne.pixels[i].red*imageTwo.pixels[i].red)/255.0) + 0.5f;
        pixelTemp.green = ((imageOne.pixels[i].green*imageTwo.pixels[i].green)/255.0) + 0.5f;
        pixelTemp.blue = ((imageOne.pixels[i].blue*imageTwo.pixels[i].blue)/255.0) + 0.5f;

        tempImage.pixels.push_back(pixelTemp);
    }
    return tempImage;
}

Image Image :: Subtract(Image& imageOne, Image& imageTwo){
    Image tempImage;
    tempImage.header = imageOne.header;
    tempImage.totalPixels = imageOne.totalPixels;

    for (int i = 0; i < imageOne.totalPixels; i++) {
        Pixel pixelTemp;
        if (((imageTwo.pixels[i].blue) - (imageOne.pixels[i].blue)) <= 0) {
            pixelTemp.blue = 0;
        }
        else {
            pixelTemp.blue = ((imageTwo.pixels[i].blue) - (imageOne.pixels[i].blue));
        }
        if (((imageTwo.pixels[i].green) - (imageOne.pixels[i].green)) <= 0) {
            pixelTemp.green = 0;
        }
        else {
            pixelTemp.green = ((imageTwo.pixels[i].green) - (imageOne.pixels[i].green));
        }
        if (((imageTwo.pixels[i].red) - (imageOne.pixels[i].red)) <= 0) {
            pixelTemp.red = 0;
        }
        else {
            pixelTemp.red = ((imageTwo.pixels[i].red) - (imageOne.pixels[i].red));
        }

        tempImage.pixels.push_back(pixelTemp);
    }
    return tempImage;
}

Image Image :: Screen(Image& imageOne, Image& imageTwo){
    Image tempImage;
    tempImage.header = imageOne.header;
    tempImage.totalPixels = imageOne.totalPixels;

    for (unsigned int i = 0; i < imageOne.totalPixels; i++) {
        Pixel pixelTemp;
        pixelTemp.red = 255.0 - ((((255.0 - imageOne.pixels[i].red) * (255.0 - imageTwo.pixels[i].red))/255.0)) + 0.5f;
        pixelTemp.green = 255.0 - ((((255.0 - imageOne.pixels[i].green) * (255.0 - imageTwo.pixels[i].green))/255.0)) + 0.5f;
        pixelTemp.blue = 255.0 - ((((255.0 - imageOne.pixels[i].blue) * (255.0 - imageTwo.pixels[i].blue))/255.0)) + 0.5f;

        tempImage.pixels.push_back(pixelTemp);
    }
    return tempImage;
}

Image Image :: Overlay(Image& imageOne, Image& imageTwo) {
    Image tempImage;
    tempImage.header = imageOne.header;
    tempImage.totalPixels = imageOne.totalPixels;

    float tempPix;
    float tempPix2;

    for (unsigned int i = 0; i < imageOne.totalPixels; i++) {
        Pixel pixelTemp;

        if (imageTwo.pixels[i].red > 127.5) {
            tempPix = (255.0 - imageTwo.pixels[i].red)/127.5;
            tempPix2 = imageTwo.pixels[i].red - (255.0 - imageTwo.pixels[i].red);

            pixelTemp.red = ((imageOne.pixels[i].red * tempPix) + tempPix2 + 0.5f);
        }
        else {
            tempPix = imageTwo.pixels[i].red/127.5;

            pixelTemp.red = (imageOne.pixels[i].red * tempPix) + 0.5f;
        }

        if (imageTwo.pixels[i].green > 127.5) {
            tempPix = (255.0 - imageTwo.pixels[i].green)/127.5;
            tempPix2 = imageTwo.pixels[i].green - (255.0 - imageTwo.pixels[i].green);

            pixelTemp.green = ((imageOne.pixels[i].green * tempPix) + tempPix2) + 0.5f;
        }
        else {
            tempPix = imageTwo.pixels[i].green/127.5;

            pixelTemp.green = (imageOne.pixels[i].green * tempPix) + 0.5f;
        }

        if (imageTwo.pixels[i].blue > 127.5) {
            tempPix = (255.0 - imageTwo.pixels[i].blue)/127.5;
            tempPix2 = imageTwo.pixels[i].blue - (255.0 - imageTwo.pixels[i].blue);

            pixelTemp.blue = ((imageOne.pixels[i].blue * tempPix) + tempPix2) + 0.5f;
        }
        else {
            tempPix = imageTwo.pixels[i].blue/127.5;

            pixelTemp.blue = (imageOne.pixels[i].blue * tempPix) + 0.5f;
        }
        tempImage.pixels.push_back(pixelTemp);
    }
    return tempImage;
}

Image Image :: AddGreen(Image& imageOne) {
    Image tempImage;
    tempImage.header = imageOne.header;
    tempImage.totalPixels = imageOne.totalPixels;

    for (unsigned int i = 0; i < imageOne.totalPixels; i++){
        Pixel pixelTemp;
        int Green;

        Green = (imageOne.pixels[i].green + 200);

        if (Green > 255) {
            Green = 255;
        }

        pixelTemp.red = imageOne.pixels[i].red;
        pixelTemp.green = Green;
        pixelTemp.blue = imageOne.pixels[i].blue;


        tempImage.pixels.push_back(pixelTemp);
    }
    return tempImage;
}

Image Image :: scaleRedBlue(Image& imageOne){
    Image tempImage;
    tempImage.header = imageOne.header;
    tempImage.totalPixels = imageOne.totalPixels;

    for (unsigned int i = 0; i < imageOne.totalPixels; i++){
        Pixel pixelTemp;
        int Red;
        int Blue;

        Red = (imageOne.pixels[i].red * 4);
        Blue = (imageOne.pixels[i].blue * 0);


        if (Red > 255) {
            Red = 255;
        }

        pixelTemp.red = Red;
        pixelTemp.green = imageOne.pixels[i].green;
        pixelTemp.blue = Blue;


        tempImage.pixels.push_back(pixelTemp);
    }
    return tempImage;
}

Image Image :: seperateRed(Image& imageOne) const{
    Image tempImage;
    tempImage.header = imageOne.header;
    tempImage.totalPixels = imageOne.totalPixels;

    for (unsigned int i = 0; i < imageOne.totalPixels; i++) {
        Pixel pixelTemp;

        pixelTemp.red = imageOne.pixels[i].red;
        pixelTemp.green = imageOne.pixels[i].red;
        pixelTemp.blue = imageOne.pixels[i].red;

        tempImage.pixels.push_back(pixelTemp);
    }
    return tempImage;
}

Image Image :: seperateGreen(Image& imageOne) const {
    Image tempImage;
    tempImage.header = imageOne.header;
    tempImage.totalPixels = imageOne.totalPixels;

    for (unsigned int i = 0; i < imageOne.totalPixels; i++) {
        Pixel pixelTemp;

        pixelTemp.red = imageOne.pixels[i].green;
        pixelTemp.green = imageOne.pixels[i].green;
        pixelTemp.blue = imageOne.pixels[i].green;

        tempImage.pixels.push_back(pixelTemp);
    }
    return tempImage;
}

Image Image :: seperateBlue(Image& imageOne) const{
    Image tempImage;
    tempImage.header = imageOne.header;
    tempImage.totalPixels = imageOne.totalPixels;

    for (unsigned int i = 0; i < imageOne.totalPixels; i++) {
        Pixel pixelTemp;

        pixelTemp.red = imageOne.pixels[i].blue;
        pixelTemp.green = imageOne.pixels[i].blue;
        pixelTemp.blue = imageOne.pixels[i].blue;

        tempImage.pixels.push_back(pixelTemp);
    }
    return tempImage;
}

Image Image :: combineLayers(Image& imageOne, Image& imageTwo, Image& imageThree){
    Image tempImage;
    tempImage.header = imageOne.header;
    tempImage.totalPixels = imageOne.totalPixels;

    for (unsigned int i = 0; i < imageOne.totalPixels; i++) {
        Pixel pixelTemp;

        pixelTemp.red = imageOne.pixels[i].red;
        pixelTemp.green = imageTwo.pixels[i].green;
        pixelTemp.blue = imageThree.pixels[i].blue;

        tempImage.pixels.push_back(pixelTemp);
    }
    return tempImage;
}

Image Image :: Rotate(Image& imageOne){
    Image tempImage;
    tempImage.header = imageOne.header;
    tempImage.totalPixels = imageOne.totalPixels;

    for (int i = (imageOne.totalPixels - 1); i >= 0; i--) {
        Pixel pixelTemp;
        pixelTemp.red = imageOne.pixels[i].red;
        pixelTemp.green = imageOne.pixels[i].green;
        pixelTemp.blue = imageOne.pixels[i].blue;

        tempImage.pixels.push_back(pixelTemp);
    }
    return tempImage;
}
int Image:: TestAll(Image& imageOne, Image& imageTwo, int count){
    bool failed = false;
    int finished = 0;

    if (imageOne.header.height != imageTwo.header.height) {
        cout << "Test#" << count << "failed" << endl;
    }
    if (imageOne.header.width != imageTwo.header.width) {
        cout << "Test#" << count << "failed" << endl;
    }
    if (imageOne.header.imageDescriptor != imageTwo.header.imageDescriptor) {
        cout << "Test#" << count << "failed" << endl;
    }
    if (imageOne.header.idLength != imageTwo.header.idLength) {
        cout << "Test#" << count << "failed" << endl;
    }
    if (imageOne.header.colorMapType != imageTwo.header.colorMapType) {
        cout << "Test#" << count << "failed" << endl;
    }
    if (imageOne.header.dataTypeCode != imageTwo.header.dataTypeCode) {
        cout << "Test#" << count << "failed" << endl;
    }
    if (imageOne.header.colorMapOrigin != imageTwo.header.colorMapOrigin) {
        cout << "Test#" << count << "failed" << endl;
    }
    if (imageOne.header.colorMapLength != imageTwo.header.colorMapLength) {
        cout << "Test#" << count << "failed" << endl;
    }
    if (imageOne.header.colorMapDepth != imageTwo.header.colorMapDepth) {
        cout << "Test#" << count << "failed" << endl;
    }
    if (imageOne.header.xOrigin != imageTwo.header.xOrigin) {
        cout << "Test#" << count << "failed" << endl;
    }
    if (imageOne.header.yOrigin != imageTwo.header.yOrigin) {
        cout << "Test#" << count << "failed" << endl;
    }
    if (imageOne.header.bitsPerPixel != imageTwo.header.bitsPerPixel) {
        cout << "Test#" << count << "failed" << endl;
    }

    for (unsigned int i = 0; i < imageOne.totalPixels; i++) {
        if(imageOne.pixels[i].red != imageTwo.pixels[i].red) {
            failed = true;
            cout << "Test #" << count << " failed at red " << i << endl;
            break;
        }
        if(imageOne.pixels[i].green != imageTwo.pixels[i].green) {
            failed = true;
            cout << "Test #" << count << " failed at green " << i << endl;
            break;
        }
        if(imageOne.pixels[i].blue != imageTwo.pixels[i].blue) {
            failed = true;
            cout << "Test #" << count << " failed at blue " << i << endl;
            break;
        }
    }
    if (!failed) {
        cout << "Test #" << count << "...... Passed!" << endl;
        finished = 1;
    }

    return finished;
}


