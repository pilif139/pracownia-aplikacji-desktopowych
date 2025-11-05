#ifndef PBMIMAGE_H
#define PBMIMAGE_H

#include <cstddef>
#include <string>


class PBMImage {
    int width;
    int height;
    bool** data;
public:
    PBMImage();
    PBMImage(int w, int h);
    ~PBMImage();

    bool loadPBM(const std::string& filename);
    bool savePBM(const std::string& filename) const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    bool** getData() const { return data; }
};


#endif // PBMIMAGE_H