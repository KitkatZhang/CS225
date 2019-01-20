#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;
using namespace std;

MyColorPicker::MyColorPicker(unsigned spacing)
	:spacing(spacing)
{	

	Color1 = HSLAPixel(11,0.8,0.5);
	Color2 = HSLAPixel(230,0.8,0.2);
	Color3 = HSLAPixel(230,0.8,0.2);
	Color4 = HSLAPixel(11,0.8,0.5);
}

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
	if (x % (2 * spacing) < spacing && y % (2 * spacing) < spacing) {
	    return Color1;
	} else if(x % (2 * spacing) >= spacing && y % (2 * spacing) < spacing){
	    return Color3;
	}else if(x % (2 * spacing) < spacing && y % (2 * spacing) >= spacing){
	    return Color2;
	}else{
	    return Color4;
	}
}
