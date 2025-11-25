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

    bool loadBinary(const std::string& filename) override;
    bool saveBinary(const std::string& filename) const override;
    bool loadAscii(const std::string& filename) override;
    bool saveAscii(const std::string& filename) const override;

    int getMaxGrayValue() const { return maxGrayValue; }
};

#endif //PGMIMAGE_H
