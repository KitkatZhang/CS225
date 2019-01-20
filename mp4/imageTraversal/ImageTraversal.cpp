#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = NULL;
  current_ = Point(unsigned(-1), unsigned(-1));
  visited = new bool[1];
}

ImageTraversal::Iterator::Iterator(ImageTraversal & traversal, Point &start, PNG & png, double tolerance)
  :traversal_(&traversal), start_(start), picture_(&png), tolerance_(tolerance)
{
  current_ = traversal_ -> peek();
  visited = new bool[picture_ -> width() * picture_ -> height()];
  for(unsigned i = 0; i < picture_ -> width() * picture_ -> height(); i++){
    visited[i] = 0;
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(!traversal_ -> empty()){
    current_ = traversal_ -> pop();
    unsigned curx = current_.x;
    unsigned cury = current_.y;

    visited[curx+cury*picture_ -> width()] = true;

    unsigned px = current_.x;
    unsigned py = current_.y;
    unsigned sx = start_.x;
    unsigned sy = start_.y;
    HSLAPixel & p2 = picture_ -> getPixel(sx, sy);
    if(px + 1 < picture_ -> width()){
      HSLAPixel & p1 = picture_ -> getPixel(px + 1, py);
      if(calculateDelta(p1, p2) < tolerance_){
        traversal_ -> add(Point(px + 1, py));
      }
    }
    if(py + 1 < picture_ -> height()){
      HSLAPixel & p5 = picture_ -> getPixel(px, py + 1);
      if(calculateDelta(p5, p2) < tolerance_){
        traversal_ -> add(Point(px, py + 1));
      }
    }
    if(int(px) - 1 >= 0){
      HSLAPixel & p4 = picture_ -> getPixel(px - 1, py);
      if(calculateDelta(p4, p2) < tolerance_){
        traversal_ -> add(Point(px - 1, py));
      }
    }
    if(int(py) - 1 >= 0){
      HSLAPixel & p3 = picture_ -> getPixel(px, py - 1);
      if(calculateDelta(p3, p2) < tolerance_){
        traversal_ -> add(Point(px, py - 1));
      }
    }
    current_ = traversal_ -> peek();
    curx = current_.x;
    cury = current_.y;
    while(visited[curx+cury*picture_ -> width()] == true){
      traversal_ -> pop();
      current_ = traversal_ -> peek();
      curx = current_.x;
      cury = current_.y;
      if(int(curx) == -1 && int(cury) == -1){
        this -> current_ = Point(-1,-1);
        traversal_ -> pop();
        return * this;
      }
    }
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return Point(current_.x, current_.y);
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(this -> current_.x == other.current_.x && this -> current_.y == other.current_.y){
    return false;
  }
  return true;
}

ImageTraversal::Iterator::~Iterator(){
  delete[] visited;
}