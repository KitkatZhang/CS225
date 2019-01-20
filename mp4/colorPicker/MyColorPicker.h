#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
	MyColorPicker(unsigned spacing);
  	HSLAPixel getColor(unsigned x, unsigned y);

private:
	HSLAPixel Color1, Color2, Color3, Color4;
  	unsigned spacing;

};
