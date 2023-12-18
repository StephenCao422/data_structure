#include <cmath>

namespace cs225 {
  typedef struct {
    unsigned char r, g, b, a; // [0, 255]
  } rgbaColor;

  typedef struct {
    double l;  // [0, 1]
  } bwColor;

  static bwColor rgb2bw(const rgbaColor & rgb) {
    double r, g, b;

    // Change rgb into [0, 1]
    r = rgb.r / 255.0;
    g = rgb.g / 255.0;
    b = rgb.b / 255.0;

    // Return result
    return {
      0.299 * r + 0.587 * g + 0.114 * b
    };
  };

  static rgbaColor bw2rgb(const bwColor & bw) {
    return {
      static_cast<unsigned char>(bw.l * 255),
      static_cast<unsigned char>(bw.l * 255),
      static_cast<unsigned char>(bw.l * 255),
      255
    };
  }
}
