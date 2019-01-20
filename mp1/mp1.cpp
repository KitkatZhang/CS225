#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <cmath>



void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG Image;
  if(Image.readFromFile(inputFile) == true){
    Image.readFromFile(inputFile);
    PNG Image1(Image.width(), Image.height());
    unsigned int h = Image.height();
    unsigned int w = Image.width();
    for(unsigned int i = 0; i < w; i ++){
      for(unsigned int j = 0; j < h; j ++){
        HSLAPixel & p1 = Image.getPixel(i, j);
        HSLAPixel & p2 = Image1.getPixel(w - 1 - i, h - 1 - j);
        p2.l = p1.l;
        p2.a = p1.a;
        p2.h = p1.h;
        p2.s = p1.s;
      }
    }
    Image1.writeToFile(outputFile);
  }
}

double distance(unsigned x1, unsigned y1, unsigned x2, unsigned y2){
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
  for(unsigned int i = 0; i < width; i ++){
    for(unsigned int j = 0; j < height; j++){
      HSLAPixel & pixel = png.getPixel(i, j);
      if(distance(i,j,i / 800 * 800 + 400, j / 800 * 800 + 400 ) < 140){
        pixel.h = 201;
        pixel.l = 0.45;
        pixel.s = 1;
        pixel.a = 1;
      }else if(distance(i,j,i / 800 * 800 + 400, j / 800 * 800 + 400 ) <= 170){
        pixel.h = 201;
        pixel.l = 1;
        pixel.s = 1;
        pixel.a = 1;
      }else if(distance(i,j,i / 800 * 800 + 400, j / 800 * 800 + 400 ) > 170
        && distance(i,j,i / 800 * 800 + 400, j / 800 * 800 + 400 ) < 400){
          if(((i % 800) >= 400 && (j % 800 < 230)) ||
          ((i % 800) <= 400 && (sqrt(3)*(int(i%800) - (400 - 147.22)) > int(j%800) - (400 + 85)) && j%800 < 485)){
            pixel.h = 360;
            pixel.l = 0.45;
            pixel.s = 0.9;
            pixel.a = 1;
          }else if(((j % 800 >= 230) && (j % 800 < 485) && (i % 800 >= 400))||
        ((j % 800 >= 485) && (0 - sqrt(3)*(int(i%800) - (400 + 147.22)) < int(j%800) - (400 + 85)))){
            pixel.h = 54;
            pixel.l = 0.54;
            pixel.s = 1;
            pixel.a = 1;
          }else{
            pixel.h = 115;
            pixel.l = 0.57;
            pixel.s = 0.66;
            pixel.a = 1;
          }
      }else{
        pixel.h = 201;
        pixel.l = 0.37;
        pixel.s = 1;
        pixel.a = 1;
      }
    }
  }
  return png;
}
