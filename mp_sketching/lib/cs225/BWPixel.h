/**
 * @file BWPixel.h
 *
 * @author CS 225: Data Structures
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
  class BWPixel {
  public:
    double l; /**< Double for the luminance of the pixel, [0, 1]. */

    /**
     * Constructs a default BWPixel. A default pixel is completely
     * opaque (non-transparent) and white.
     */
    BWPixel();

    /**
     * Constructs an opaque BWPixel with the given luminance value.
     * @param luminance Luminance value for the new pixel, [0, 1].
     */
    BWPixel(double luminance);

    bool operator== (BWPixel const & other) const;
    bool operator!= (BWPixel const & other) const;
    bool operator<  (BWPixel const & other) const;
  };

  /**
   * Stream operator that allows pixels to be written to standard streams
   * (like cout).
   *
   * @param out Stream to write to.
   * @param pixel Pixel to write to the stream.
   */
  std::ostream & operator<<(std::ostream & out, BWPixel const & pixel);
  std::stringstream & operator<<(std::stringstream & out, BWPixel const & pixel);
}
