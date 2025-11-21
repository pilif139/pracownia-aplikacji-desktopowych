#ifndef PBMIMAGE_H
#define PBMIMAGE_H

#include <string>
#include "Image.h"

class PBMImage : public Image {
public:
    PBMImage();
    PBMImage(int w, int h);
    ~PBMImage() override;

    // Override virtual methods from Image base class (uses binary P4 format)
    bool load(const std::string& filename) override;
    bool save(const std::string& filename) const override;
};


#endif // PBMIMAGE_H