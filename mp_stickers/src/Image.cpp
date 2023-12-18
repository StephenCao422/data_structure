#include "Image.h"

using namespace cs225;

    Image::Image():PNG(){}

    Image::Image(unsigned int width, unsigned int height):PNG(width,height){}

    void Image::lighten (){
        for (unsigned int i=0;i<width();i++){
            for (unsigned int j=0;j<height();j++){
                HSLAPixel& p = getPixel(i,j);
                p.l += 0.1;
                if (p.l < 0){
                    p.l = 0;
                }
                if (p.l > 1){
                    p.l = 1;
                }
            }
        }
    }
    void Image::lighten (double amount){
        for (unsigned int i=0;i<width();i++){
            for (unsigned int j=0;j<height();j++){
                HSLAPixel& p = getPixel(i,j);
                p.l += amount;
                if (p.l < 0){
                    p.l = 0;
                }
                if (p.l > 1){
                    p.l = 1;
                }
            }
        }
    }
    void Image::darken(){
        for (unsigned int i=0;i<width();i++){
            for (unsigned int j=0;j<height();j++){
                HSLAPixel& p = getPixel(i,j);
                p.l -= 0.1;
                if (p.l < 0){
                    p.l = 0;
                }
                if (p.l > 1){
                    p.l = 1;
                }
            }
        }
    }
    void Image::darken(double amount){
        for (unsigned int i=0;i<width();i++){
            for (unsigned int j=0;j<height();j++){
                HSLAPixel& p = getPixel(i,j);
                p.l -= amount;
                if (p.l < 0){
                    p.l = 0;
                }
                if (p.l > 1){
                    p.l = 1;
                }
            }
        }
    }
    void Image::saturate(){
        for (unsigned int i=0;i<width();i++){
            for (unsigned int j=0;j<height();j++){
                HSLAPixel& p = getPixel(i,j);
                p.s += 0.1;
                if (p.s < 0){
                    p.s = 0;
                }
                if (p.s > 1){
                    p.s = 1;
                }
            }
        }
    }
    void Image::saturate(double amount){
        for (unsigned int i=0;i<width();i++){
            for (unsigned int j=0;j<height();j++){
                HSLAPixel& p = getPixel(i,j);
                p.s += amount;
                if (p.s < 0){
                    p.s = 0;
                }
                if (p.s > 1){
                    p.s = 1;
                }
            }
        }
    }
    void Image::desaturate(){
        for (unsigned int i=0;i<width();i++){
            for (unsigned int j=0;j<height();j++){
                HSLAPixel& p = getPixel(i,j);
                p.s -= 0.1;
                if (p.s < 0){
                    p.s = 0;
                }
                if (p.s > 1){
                    p.s = 1;
                }
            }
        }
    }
    void Image::desaturate(double amount){
        for (unsigned int i=0;i<width();i++){
            for (unsigned int j=0;j<height();j++){
                HSLAPixel& p = getPixel(i,j);
                p.s -= amount;
                if (p.s < 0){
                    p.s = 0;
                }
                if (p.s > 1){
                    p.s = 1;
                }
            }
        }
    }
    void Image::grayscale(){
        for (unsigned int i=0;i<width();i++){
            for (unsigned int j=0;j<height();j++){
                HSLAPixel& p = getPixel(i,j);
                p.s = 0;
            }
        }
    }
    void Image::rotateColor(double degrees){
        for (unsigned int i=0;i<width();i++){
            for (unsigned int j=0;j<height();j++){
                HSLAPixel& p = getPixel(i,j);
                p.h += degrees;
                if (p.h > 360){
                    p.h -= 360;
                }
                if (p.h < 0){
                    p.h += 360;
                }
            }
        }
    }
    void Image::illinify(){
        for (unsigned int i=0;i<width();i++){
            for (unsigned int j=0;j<height();j++){
                HSLAPixel& p = getPixel(i,j);
                if (p.h < 11){
                    p.h = 11;                    
                }
                else if(p.h > 216){
                    p.h = 216;
                }
                else if( 11 < p.h && p.h < 216){
                    if((216-p.h) > (p.h-11)){
                        p.h = 11;
                    }
                    else{
                        p.h = 216;
                    }
                }
            }
        }
    }

    void Image::scale(double factor) {
        unsigned newWidth = static_cast<unsigned>(width() * factor);
        unsigned newHeight = static_cast<unsigned>(height() * factor);
        cs225::PNG scaledImage(newWidth, newHeight);

        for (unsigned x = 0; x < newWidth; x++) {
            for (unsigned y = 0; y < newHeight; y++) {
                unsigned origX = static_cast<unsigned>(x / factor);
                unsigned origY = static_cast<unsigned>(y / factor);

                scaledImage.getPixel(x, y) = this->getPixel(origX, origY);
            }
        }
        this->resize(newWidth, newHeight);
        for (unsigned x = 0; x < newWidth; x++) {
            for (unsigned y = 0; y < newHeight; y++) {
                this->getPixel(x, y) = scaledImage.getPixel(x, y);
            }
        }
    }

    void Image::scale(unsigned w, unsigned h) {
        double factor_x = (double)w / (double)this->width();
        double factor_y = (double)h / (double)this->height();
        // double factor = std::min(factor_x, factor_y);
        // scale(factor);
        (factor_x < factor_y) ? scale(factor_x) : scale(factor_y);
    }