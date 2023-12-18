#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  unsigned i = x;
  unsigned j = y;
  double h = (i+j)%360;
  return HSLAPixel(h,1.0,0.5);
}

MyColorPicker::MyColorPicker(HSLAPixel color){
  this->color = color;
}