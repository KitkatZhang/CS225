#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
	png_ = png;
  it = new ImageTraversal*[20];
  newcolor = new ColorPicker*[20];
  for(int i = 0; i < 20; i++){
    it[i] = NULL;
    newcolor[i] = NULL;
  }
  cnt = 0;
  cntmax = 20;
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  if(cnt < cntmax){
    it[cnt] = &traversal;
    newcolor[cnt] = &colorPicker;
    cnt++;
  }else{
    ImageTraversal ** temp = it;
    ColorPicker ** temp1 = newcolor;
    cntmax = 2 * cntmax;
    it = new ImageTraversal*[cntmax];
    newcolor = new ColorPicker*[cntmax]; 
    for(int i = 0; i < cnt; i++){
      it[i] = temp[i];
      newcolor[i] = temp1[i];
    }
    it[cnt] = &traversal;
    newcolor[cnt] = &colorPicker;
    cnt++;
    delete[] temp;
    delete[] temp1;
  }
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  int count = 0;
  for(int i = 0; i < cnt; i++){
    for(ImageTraversal::Iterator it1 = (*it[i]).begin(); it1 != (*it[i]).end(); ++it1){
      if(count % frameInterval == 0){
        animation.addFrame(png_);
      }
      Point temp = *it1;
      png_.getPixel(temp.x, temp.y) = (newcolor[i] -> getColor(temp.x, temp.y));
      count++;
    }
    animation.addFrame(png_);
  }
  return animation;
}

FloodFilledImage::~FloodFilledImage(){
  delete[] it;
  delete[] newcolor;
}
