/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

using namespace cs225;
class StickerSheet{
    public:
        StickerSheet (const Image &picture, unsigned max);
        ~StickerSheet();
        void clear();
        void copy(const StickerSheet& other);
        StickerSheet (const StickerSheet &other);
        const StickerSheet & operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, int x, int y);
        int setStickerAtLayer (Image &sticker, unsigned layer, int x, int y);
        bool translate (unsigned index, int x, int y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        int layers () const; 
        Image render () const;
    private:
        unsigned* x_;
        unsigned* y_;
        Image** sticker_;
        Image base;
        unsigned int index_;
        unsigned int max_;
};