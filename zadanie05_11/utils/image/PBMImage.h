#ifndef PBMIMAGE_H
#define PBMIMAGE_H

#include <string>
#include "Image.h"

class PBMImage : public Image {
public:
    PBMImage();
    PBMImage(int w, int h);
    ~PBMImage() override;

    // Override virtual methods from Image base class
    bool loadBinary(const std::string& filename) override;
    bool saveBinary(const std::string& filename) const override;
    bool loadAscii(const std::string& filename) override;
    bool saveAscii(const std::string& filename) const override;
};


#endif // PBMIMAGE_H