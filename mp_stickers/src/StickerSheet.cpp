#include "StickerSheet.h"

using namespace cs225;

StickerSheet::StickerSheet (const Image &picture, unsigned max){
    index_ = 0;
    max_ = max;
    base = picture;
    sticker_ = new Image* [max];
    for(unsigned int i = 0; i < max_; i++){
      sticker_[i] = NULL;
    }
    x_ = new unsigned [max];
    y_ = new unsigned [max];
}

StickerSheet::~StickerSheet(){
  if(x_ != NULL){
    delete[] x_;
    x_= NULL;
  }
  
  if(y_ != NULL){
    delete[] y_;
    y_= NULL;
  }

  if(sticker_ != NULL){
    for (unsigned int i=0; i<max_; i++){
      sticker_[i] = NULL;
    }
    delete[] sticker_;
    sticker_ = NULL;
  }
}

StickerSheet::StickerSheet (const StickerSheet &other){
    index_ = other.index_;
    max_ = other.max_;
    base = other.base;
    x_ = new unsigned [max_];
    y_ = new unsigned [max_];
    sticker_ = new Image* [max_];
    for (unsigned int i=0; i<max_; i++){
        x_[i] = other.x_[i];
        y_[i] = other.y_[i];
        sticker_[i] = other.sticker_[i];
    }
}

const StickerSheet& StickerSheet::operator= (const StickerSheet &other){
  if(x_ != NULL){
    delete[] x_;
    x_= NULL;
  }
  
  if(y_ != NULL){
    delete[] y_;
    y_= NULL;
  }

  if(sticker_ != NULL){
    for (unsigned int i=0; i<max_; i++){
      sticker_[i] = NULL;
    }
    delete[] sticker_;
    sticker_ = NULL;
  }

  if(&other != this){
    index_ = other.index_;
    max_ = other.max_;
    base = other.base;
    x_ = new unsigned [max_];
    y_ = new unsigned [max_];
    sticker_ = new Image* [max_];
    for (unsigned int i=0; i<max_; i++){
        x_[i] = other.x_[i];
        y_[i] = other.y_[i];
        sticker_[i] = other.sticker_[i];
    }
  }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  unsigned maxOrig = max_;
  max_ = max;
  if(max_ == maxOrig){
    return;
  }
  unsigned * x_New = new unsigned[max_];
  unsigned * y_New = new unsigned[max_];
  Image ** sheetNew = new Image *[max_];
  if(max_ < maxOrig) {
    for(unsigned i = 0; i < max_; i++) {
      //if(sticker_[i] != NULL){
        x_New[i] = x_[i];
        y_New[i] = y_[i];
        //sheetNew[i] = new Image(*sticker_[i]);
        sheetNew[i] = sticker_[i];
      //}
      //else {
       // x_New[i] = 0;
        //y_New[i] = 0;
        //sheetNew[i] = NULL;
      //}
    }
    if(index_ > max_) {
      index_ = max_;
    }
  }
  else if(max_ > maxOrig){
    for(unsigned i = 0; i < max_; i++) {
      x_New[i] = 0;
      y_New[i] = 0;
      sheetNew[i] = NULL;
    }
    for(unsigned i = 0; i < maxOrig; i++) {
      //if(sticker_[i] != NULL) {
        x_New[i] = x_[i];
        y_New[i] = y_[i];
        //sheetNew[i] = new Image(*sticker_[i]);
        sheetNew[i] = sticker_[i];
      //}
    }
  }
  // //for(unsigned i = 0; i < maxOrig; i++) {
  //   delete sticker_[i];
  //   sticker_[i] = NULL;
  // //}
  
  delete[] x_;
  delete[] y_;
  delete[] sticker_;
  x_ = x_New;
  y_ = y_New;
  sticker_ = sheetNew;
}
/*
void StickerSheet::changeMaxStickers (unsigned max){
  Image** new_sticker = new Image* [max];
  unsigned* new_x = new unsigned [max];
  unsigned* new_y = new unsigned [max];

  if (max_ > max){
    for (unsigned int i=0; i<max; i++){
      new_x[i] = x_[i];
      new_y[i] = y_[i];
      new_sticker[i] = sticker_[i];
    }
    clear();
  }
  if(max_ < max){
    for (unsigned int i=0; i<max_; i++){
      new_x[i] = x_[i];
      new_y[i] = y_[i];
      new_sticker[i] = sticker_[i];
    }
    //clear();
  }
  if(max_ == max){
    for (unsigned int i=0; i<max_; i++){
      new_x[i] = x_[i];
      new_y[i] = y_[i];
      new_sticker[i] = sticker_[i];
    }
    clear();
  }
    //max_ = max;
  
  //max_ = max;
	sticker_ =new_sticker;
	x_ = new_x;
	y_ = new_y;
  max_ = max;
}
*/

int StickerSheet::addSticker (Image &sticker, int x, int y){
  bool add = false;

    for(unsigned i = 0; i < max_; i++) {
      if(sticker_[i] == NULL) {
          sticker_[i] = &sticker;
          x_[i] = x;
          y_[i] = y;
          index_++;
          add = true;
          return i;
      }
      //break;
    }

    if (!add){
      StickerSheet::changeMaxStickers(max_+1);
      for(unsigned i = 0; i < max_; i++) {
        if(sticker_[i] == NULL) {
            sticker_[i] = &sticker;
            x_[i] = x;
            y_[i] = y;
            index_++;
            add = true;
            return i;
        }
      }
    }
  return -1;
}

/*
        if (index_ == max_){
          StickerSheet::changeMaxStickers(max_+1);
          sticker_[index_] = &sticker;
          x_[index_] = x;
          y_[index_] = y;
          index_++;
          return max_- 1;
        }
    
          sticker_[index_] =&sticker;
          x_[index_] = x;
          y_[index_] = y;
          index_++;
          return index_ - 1;
*/

int StickerSheet::setStickerAtLayer (Image &sticker, unsigned layer, int x, int y){
  if (layer >= max_){
    return -1;
  }
  else{
    if (sticker_[layer] != NULL){
      //delete sticker_[layer];
      sticker_[layer] = NULL;
    }
    sticker_[layer] = &sticker;
    x_[layer] = x;
    y_[layer] = y;
    //index_++;
  }
  return layer;
}

bool StickerSheet::translate (unsigned index, int x, int y){
    /*if (index >= index_ || sticker_[index]==nullptr) {
      return false;
    }
    */
    if (index < index_){
      x_[index] = x;
		  y_[index] = y;
		  return true;
    }
    return false;
}

void StickerSheet::removeSticker (unsigned index){
  if(index >= max_ || sticker_[index]==NULL){
    return;
  }
  /*
    delete sticker_[index];
    for (unsigned i = index; i < max_- 1; i++) {
		sticker_[i] = sticker_[i + 1];
		x_[i] = x_[i + 1];
		y_[i] = y_[i + 1];
	}
	index_--;
  */
  sticker_[index] = NULL;
  x_[index] = 0;
  y_[index] = 0;
  index_ --;
}

Image* StickerSheet::getSticker (unsigned index){
  if (index >= max_ || index_<0) {
    return NULL;
  }
	return sticker_[index];
}

int StickerSheet::layers() const{
    return max_;
}

Image StickerSheet::render() const {
    int min_x = 0, min_y = 0;
    int max_x = static_cast<int>(base.width());
    int max_y = static_cast<int>(base.height());

    for (unsigned i = 0; i < max_; i++) {
        if (sticker_[i] != nullptr) {
            min_x = std::min(min_x, (int)(x_[i]));
            min_y = std::min(min_y, (int)(y_[i]));
            max_x = std::max(max_x, (int)(x_[i] + sticker_[i]->width()));
            max_y = std::max(max_y, (int)(y_[i] + sticker_[i]->height()));
        }
    }
    Image result;
    result.resize(max_x - min_x, max_y - min_y);
    for (int x = 0; x < (int)(base.width()); x++) { 
        for (int y = 0; y < (int)(base.height()); y++) {
            result.getPixel(x - min_x, y - min_y) = base.getPixel(x, y);
        }
    }
    for (unsigned layer = 0; layer < max_; layer++) {
        if (sticker_[layer] != nullptr) {
            for (int x = 0; x < (int)(sticker_[layer]->width()); x++) {
                for (int y = 0; y < (int)(sticker_[layer]->height()); y++) {
                    if (sticker_[layer]->getPixel(x, y).a != 0) { 
                        result.getPixel(x_[layer] + x - min_x, y_[layer] + y - min_y) = sticker_[layer]->getPixel(x, y);
                    }
                }
            }
        }
    }
    return result;
}
