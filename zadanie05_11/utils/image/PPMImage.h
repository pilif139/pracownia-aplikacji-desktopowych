#ifndef PPMIMAGE_H
#define PPMIMAGE_H

#include <string>
#include "Image.h"

class PPMImage : public Image
{
    int maxColorValue = 255;

public:
    PPMImage();
    PPMImage(int w, int h, int maxVal = 255);
    ~PPMImage() override;

    // Override virtual methods from Image base class (uses binary P6 format)
    bool load(const std::string &filename) override;
    bool save(const std::string &filename) const override;

    int getMaxColorValue() const { return maxColorValue; }
};

#endif // PPMIMAGE_H
