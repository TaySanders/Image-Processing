
#include <iomanip>
#include <iostream>
#include "Image.h"

using namespace std;

int main()
{

    /// Part One ///
    Image object;
    Image objectTwo;
    object.readFileHeader("input/layer1.tga");
    objectTwo.readFileHeader("input/pattern1.tga");
    Image partOne = object.Multiply(object, objectTwo);
    partOne.writeToFile("output/part1.tga");


    /// Part Two ///

    Image object2;
    Image objectTwo2;
    object2.readFileHeader("input/layer2.tga");
    objectTwo2.readFileHeader("input/car.tga");
    Image partTwo = object2.Subtract(object2, objectTwo2);
    partTwo.writeToFile("output/part2.tga");


    /// Part Three ///
    Image object3;
    Image objectTwo3;
    Image objectThree3;
    object3.readFileHeader("input/layer1.tga");
    objectTwo3.readFileHeader("input/pattern2.tga");
    objectThree3.readFileHeader("input/text.tga");

    Image partThreeTemp = object3.Multiply(object3, objectTwo3);

    Image partThree = object3.Screen(partThreeTemp, objectThree3);

    partThree.writeToFile("output/part3.tga");


    /// Part Four ///
    Image object4;
    Image objectTwo4;
    Image objectThree4;

    object4.readFileHeader("input/layer2.tga");
    objectTwo4.readFileHeader("input/circles.tga");
    objectThree4.readFileHeader("input/pattern2.tga");

    Image partFourTemp = object4.Multiply(object4, objectTwo4);

    Image partFour = object4.Subtract(objectThree4, partFourTemp);

    partFour.writeToFile("output/part4.tga");



    /// Part Five ///
    Image object5;
    Image objectTwo5;

    object5.readFileHeader("input/layer1.tga");
    objectTwo5.readFileHeader("input/pattern1.tga");

    Image partFive = object5.Overlay(object5,objectTwo5);

    partFive.writeToFile("output/part5.tga");


    /// Part Six ///
    Image object6;

    object6.readFileHeader("input/car.tga");

    Image partSix = object6.AddGreen(object6);

    partSix.writeToFile("output/part6.tga");


    /// Part Seven ///
    Image object7;

    object7.readFileHeader("input/car.tga");

    Image partSeven = object7.scaleRedBlue(object7);

    partSeven.writeToFile("output/part7.tga");


    /// Part Eight ///
    Image object8r;
    Image object8g;
    Image object8b;

    object8r.readFileHeader("input/car.tga");
    object8g.readFileHeader("input/car.tga");
    object8b.readFileHeader("input/car.tga");

    Image part8_r= object8r.seperateRed(object8r);
    Image part8_g = object8g.seperateGreen(object8g);
    Image part8_b = object8b.seperateBlue(object8b);

    part8_r.writeToFile("output/part8_r.tga");
    part8_g.writeToFile("output/part8_g.tga");
    part8_b.writeToFile("output/part8_b.tga");


    /// Part Nine ///
    Image object9;
    Image objectTwo9;
    Image objectThree9;

    object9.readFileHeader("input/layer_red.tga");
    objectTwo9.readFileHeader("input/layer_green.tga");
    objectThree9.readFileHeader("input/layer_blue.tga");

    Image partNine = object9.combineLayers(object9, objectTwo9, objectThree9);

    partNine.writeToFile("output/part9.tga");


    /// Part Ten ///
    Image object10;

    object10.readFileHeader("input/text2.tga");

    Image partTen = object10.Rotate(object10);

    partTen.writeToFile("output/part10.tga");

    /// Test Files ///
    int totalCount = 0;

    Image exampleOne;
    exampleOne.readFileHeader("examples/EXAMPLE_part1.tga");
    totalCount += exampleOne.TestAll(partOne, exampleOne, 1);

    Image exampleTwo;
    exampleTwo.readFileHeader("examples/EXAMPLE_part2.tga");
    totalCount += exampleTwo.TestAll(partTwo, exampleTwo, 2);

    Image exampleThree;
    exampleThree.readFileHeader("examples/EXAMPLE_part3.tga");
    totalCount += exampleThree.TestAll(partThree, exampleThree, 3);

    Image exampleFour;
    exampleFour.readFileHeader("examples/EXAMPLE_part4.tga");
    totalCount += exampleFour.TestAll(partFour, exampleFour, 4);

    Image exampleFive;
    exampleFive.readFileHeader("examples/EXAMPLE_part5.tga");
    totalCount += exampleFive.TestAll(partFive, exampleFive, 5);

    Image exampleSix;
    exampleSix.readFileHeader("examples/EXAMPLE_part6.tga");
    totalCount += exampleSix.TestAll(partSix, exampleSix, 6);

    Image exampleSeven;
    exampleSeven.readFileHeader("examples/EXAMPLE_part7.tga");
    totalCount += exampleSeven.TestAll(partSeven, exampleSeven, 7);

    Image exampleEightB;
    exampleEightB.readFileHeader("examples/EXAMPLE_part8_b.tga");
    totalCount += exampleEightB.TestAll(part8_b, exampleEightB, 8);

    Image exampleEightG;
    exampleEightG.readFileHeader("examples/EXAMPLE_part8_g.tga");
    totalCount += exampleEightG.TestAll(part8_g, exampleEightG, 8);

    Image exampleEightR;
    exampleEightR.readFileHeader("examples/EXAMPLE_part8_r.tga");
    totalCount += exampleEightR.TestAll(part8_r, exampleEightR, 8);

    Image exampleNine;
    exampleNine.readFileHeader("examples/EXAMPLE_part9.tga");
    totalCount += exampleNine.TestAll(partNine, exampleNine, 9);

    Image exampleTen;
    exampleTen.readFileHeader("examples/EXAMPLE_part10.tga");
    totalCount += exampleTen.TestAll(partTen, exampleTen, 10);

    cout << "Test results: " << totalCount<< " / 12" << endl;
}




