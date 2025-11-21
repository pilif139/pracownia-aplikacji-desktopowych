#ifndef PGMIMAGE_H
#define PGMIMAGE_H

#include <string>
#include "Image.h"

class PGMImage : public Image {
private:
    int maxGrayValue = 255;

public:
    PGMImage();
    PGMImage(int w, int h, int maxVal = 255);
    ~PGMImage() override;

    bool load(const std::string& filename) override;
    bool save(const std::string& filename) const override;

    int getMaxGrayValue() const { return maxGrayValue; }
};

#endif //PGMIMAGE_H
