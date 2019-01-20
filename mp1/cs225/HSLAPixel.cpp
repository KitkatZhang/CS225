/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
    HSLAPixel::HSLAPixel() {
        this -> l = 1;
        this -> s = 0;
        this -> a = 1;
        this -> h = 0;
    }
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminance) {
        if(hue >= 0 && hue < 360){this -> h = hue;}
        else{
            cout << "Invalid hue!";
            this -> h = 0;
        }
        if(saturation >= 0 && saturation <=1){this -> s = saturation;}
        else{
            cout << "Invalid saturation!";
            this -> s = 0;
        }
        if(luminance >= 0 && luminance <=1){this -> l = luminance;}
        else{
            cout << "Invalid luminance!";
            this -> l = 1;
        }
        this -> a = 1;

    }
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha) {
        if(hue >= 0 && hue < 360){this -> h = hue;}
        else{
            cout << "Invalid hue!";
            this -> h = 0;
        }
        if(saturation >= 0 && saturation <=1){this -> s = saturation;}
        else{
            cout << "Invalid saturation!";
            this -> s = 0;
        }
        if(luminance >= 0 && luminance <=1){this -> l = luminance;}
        else{
            cout << "Invalid luminance!";
            this -> l = 1;
        }
        if(alpha >= 0 && alpha <=1){this -> a = alpha;}
        else{
            cout << "Invalid alpha!";
            this -> a = 0;
        }
    }

}
