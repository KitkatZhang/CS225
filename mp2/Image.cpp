#include "Image.h"
#include <iostream>
using namespace std;

void Image::lighten(){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  for(unsigned int i = 0; i < w; i++){
    for(unsigned int j = 0; j < h; j++){
      HSLAPixel & pixel = getPixel(i, j);
      if(pixel.l > 0.9){
        pixel.l = 1;
      }else{
        pixel.l += 0.1;
      }
    }
  }
}
void Image::lighten(double amount){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  for(unsigned int i = 0; i < w; i++){
    for(unsigned int j = 0; j < h; j++){
      HSLAPixel & pixel = getPixel(i, j);
      if(pixel.l > 1 - amount){
        pixel.l = 1;
      }else{
        pixel.l += amount;
      }
    }
  }
}
void Image::darken(){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  for(unsigned int i = 0; i < w; i++){
    for(unsigned int j = 0; j < h; j++){
      HSLAPixel & pixel = getPixel(i, j);
      if(pixel.l < 0.1){
        pixel.l = 0;
      }else{
        pixel.l -= 0.1;
      }
    }
  }
}
void Image::darken(double amount){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  for(unsigned int i = 0; i < w; i++){
    for(unsigned int j = 0; j < h; j++){
      HSLAPixel & pixel = getPixel(i, j);
      if(pixel.l < amount){
        pixel.l = 0;
      }else{
        pixel.l -= amount;
      }
    }
  }
}
void Image::saturate(){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  for(unsigned int i = 0; i < w; i++){
    for(unsigned int j = 0; j < h; j++){
      HSLAPixel & pixel = getPixel(i, j);
      if(pixel.s > 0.9){
        pixel.s = 1;
      }else{
        pixel.s += 0.1;
      }
    }
  }
}
void Image::saturate(double amount){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  for(unsigned int i = 0; i < w; i++){
    for(unsigned int j = 0; j < h; j++){
      HSLAPixel & pixel = getPixel(i, j);
      if(pixel.s > 1 - amount){
        pixel.s = 1;
      }else{
        pixel.s += amount;
      }
    }
  }
}
void Image::desaturate(){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  for(unsigned int i = 0; i < w; i++){
    for(unsigned int j = 0; j < h; j++){
      HSLAPixel & pixel = getPixel(i, j);
      if(pixel.s < 0.1){
        pixel.s = 0;
      }else{
        pixel.s -= 0.1;
      }
    }
  }
}
void Image::desaturate(double amount){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  for(unsigned int i = 0; i < w; i++){
    for(unsigned int j = 0; j < h; j++){
      HSLAPixel & pixel = getPixel(i, j);
      if(pixel.s < amount){
        pixel.s = 0;
      }else{
        pixel.s -= amount;
      }
    }
  }
}
void Image::grayscale(){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = 0;
    }
  }
}
void Image::rotateColor(double degrees){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.h = (pixel.h + degrees);
      if(pixel.h >= 360){
        pixel.h -= 360;
      }
      if(pixel.h < 0){
        pixel.h += 360;
      }
    }
  }
}
void Image::illinify(){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if(pixel.h > 11 && pixel.h < 216){
        double disO = std::abs(pixel.h - 11);
        double disB = std::abs(216 - pixel.h);
        if(disO > disB){
          pixel.h = 216;
        }else{
          pixel.h = 11;
        }
      }else if(pixel.h < 11 || pixel.h > 216){
        double disO; double disB;
        if(pixel.h < 11){
          pixel.h = 11;
        }else{
          disO = 360 - pixel.h + 11;
          disB = pixel.h - 216;
          if(disO > disB){
            pixel.h = 216;
          }else{
            pixel.h = 11;
          }
        }
      }
    }
  }
}
void Image::scale(double factor){
  unsigned int h = this -> height();
  unsigned int w = this -> width();
  unsigned int h1 = unsigned(int(double(h * factor)));
  unsigned int w1 = unsigned(int(double(w * factor)));
  HSLAPixel *imageDatatemp = new HSLAPixel[w * h];
  for (unsigned i = 0; i < w * h; i++) {
    HSLAPixel & pixel = getPixel(i % w, i / w);
    imageDatatemp[i].h = pixel.h;
    imageDatatemp[i].s = pixel.s;
    imageDatatemp[i].l = pixel.l;
    imageDatatemp[i].a = pixel.a;
  }
  this -> resize(w1, h1);
  for (unsigned x = 0; x < w; x++) {
    for (unsigned y = 0; y < h; y++) {
      for(unsigned i = x * factor; i < (x + 1) * factor && i < w1; i++){
        for(unsigned j = y * factor; j < (y + 1) * factor && j < h1; j++){
          HSLAPixel & pixel = getPixel(i, j);
          pixel.h = imageDatatemp[y*w+x].h;
          pixel.s = imageDatatemp[y*w+x].s;
          pixel.l = imageDatatemp[y*w+x].l;
          pixel.a = imageDatatemp[y*w+x].a;
        }
      }
    }
  }
  delete[] imageDatatemp;
}

void Image::scale(unsigned w, unsigned h){
  double factor;

  factor = (double(this -> height()) / h) > (double(this -> width()) / w) ?  (double(this -> height()) / h) : (double(this -> width()) / w);
  factor = 1 / factor;
  this -> scale(factor);
}
