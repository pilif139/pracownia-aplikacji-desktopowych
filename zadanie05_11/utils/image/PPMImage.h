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

    bool loadBinary(const std::string &filename) override;
    bool saveBinary(const std::string &filename) const override;

    bool loadAscii(const std::string &filename) override;
    bool saveAscii(const std::string &filename) const override;

    int getMaxColorValue() const { return maxColorValue; }
};

#endif // PPMIMAGE_H
