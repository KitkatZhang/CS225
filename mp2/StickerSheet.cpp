#include "StickerSheet.h"
#include "Image.h"
using namespace std;

StickerSheet::StickerSheet(const Image & picture, unsigned max){
  basepic = picture;
  maxLength = max;
  stickerarray = new Image*[maxLength];
  xarray = new unsigned[maxLength];
  yarray = new unsigned[maxLength];
  for(unsigned i = 0; i < maxLength; i++){
    xarray[i] = -1;
    yarray[i] = -1;
  }
}

StickerSheet::~StickerSheet(){

  delete[] this -> stickerarray;
  this -> stickerarray = NULL;
  delete[] this -> xarray;
  this -> xarray = NULL;
  delete[] this -> yarray;
  this -> yarray = NULL;
}

StickerSheet::StickerSheet(const StickerSheet & other){
  this -> basepic = other.basepic;
  this -> maxLength = other.maxLength;
  this -> xarray = new unsigned[maxLength];
  this -> yarray = new unsigned[maxLength];
  this -> stickerarray = new Image*[this -> maxLength];
  for(unsigned i = 0; i < this -> maxLength; i++){
    this -> stickerarray[i] = other.stickerarray[i];
    this -> xarray[i] = other.xarray[i];
    this -> yarray[i] = other.yarray[i];
  }
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
  if(this != &other){
    delete[] this -> stickerarray;
    this -> stickerarray = NULL;
    delete[] this -> xarray;
    this -> xarray = NULL;
    delete[] this -> yarray;
    this -> yarray = NULL;

    this -> basepic = other.basepic;
    this -> maxLength = other.maxLength;
    this -> xarray = new unsigned[maxLength];
    this -> yarray = new unsigned[maxLength];
    this -> stickerarray = new Image*[this -> maxLength];
    for(unsigned i = 0; i < this -> maxLength; i++){
      this -> stickerarray[i] = other.stickerarray[i];
      this -> xarray[i] = other.xarray[i];
      this -> yarray[i] = other.yarray[i];
    }
  }
  return * this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if(this -> maxLength != max){
    Image ** temp = this -> stickerarray;
    unsigned * tempx = this -> xarray;
    unsigned * tempy = this -> yarray;
    this -> xarray = NULL;
    this -> yarray = NULL;
    this -> stickerarray = NULL;
    unsigned templength = this -> maxLength;
    this -> maxLength = max;
    this -> stickerarray = new Image*[maxLength];
    this -> xarray = new unsigned[maxLength];
    this -> yarray = new unsigned[maxLength];
    for(unsigned i = 0; i < maxLength; i ++){
      if(i < templength){
        this -> stickerarray[i] = temp[i];
        this -> xarray[i] = tempx[i];
        this -> yarray[i] = tempy[i];
      }else{
        this -> xarray[i] = -1;
        this -> yarray[i] = -1;
      }
    }
    delete[] temp;
    delete[] tempx;
    delete[] tempy;
    tempx = NULL;
    tempy = NULL;
    temp = NULL;
  }
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
  for(unsigned i = 0; i < maxLength; i++){
    if(xarray[i] == unsigned(-1)){
      stickerarray[i] = &sticker;
      xarray[i] = x;
      yarray[i] = y;
      return i;
    }
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(xarray[index] != unsigned(-1)){
    xarray[index] = x;
    yarray[index] = y;
    return 1;
  }
  return 0;
}

void StickerSheet::removeSticker(unsigned index){
  xarray[index] = -1;
  yarray[index] = -1;
}

Image * StickerSheet::getSticker(unsigned index) const{
  if(xarray[index] != unsigned(-1)){
    return stickerarray[index];
  }
  return NULL;
}

Image StickerSheet::render() const{
  for(unsigned i = 0; i < maxLength; i ++){
    if(xarray[i] != unsigned(-1)){
      unsigned h = stickerarray[i]->height();
      unsigned w = stickerarray[i]->width();
      for(unsigned x = xarray[i]; x < xarray[i] + w && x < basepic.width(); x++){
        for(unsigned y = yarray[i]; y < yarray[i] + h && y < basepic.height(); y++){
          HSLAPixel & pixel = basepic.getPixel(x, y);
          HSLAPixel & pixel1 = stickerarray[i]->getPixel(x - xarray[i], y - yarray[i]);
          if(pixel1.a != 0){
            pixel.h = pixel1.h;
            pixel.s = pixel1.s;
            pixel.l = pixel1.l;
            pixel.a = pixel1.a;
          }
        }
      }

    }
  }
  return basepic;
}
