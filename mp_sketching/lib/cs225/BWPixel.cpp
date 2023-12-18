/**
 * @file BWPixel.cpp
 * Implementation of the BWPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 */

#include "BWPixel.h"
#include <cmath>
#include <iostream>

namespace cs225 {
  BWPixel::BWPixel() {
    l = 1.0;
  }

  BWPixel::BWPixel(double luminance) {
    l = luminance;
  }

  bool BWPixel::operator== (BWPixel const & other) const {
    return fabs(l - other.l) <= 0.0000001;
  }

  bool BWPixel::operator!= (BWPixel const & other) const {
    return !(*this == other);
  }

  bool BWPixel::operator<  (BWPixel const & other) const {
    return l < other.l;
  }

  std::ostream & operator<<(std::ostream & out, BWPixel const & pixel) {
    out << "(" << pixel.l << ")";

    return out;
  }


}
