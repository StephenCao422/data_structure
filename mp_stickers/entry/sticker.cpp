#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
#include "assert.h"

using namespace cs225;

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  alma.readFromFile("tests/alma.png");

  Image i;
  i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 3);
  sheet.addSticker(i, 20, 200);

  Image final = sheet.render();
  final.writeToFile("myImage.png");
  
  return 0;
}
