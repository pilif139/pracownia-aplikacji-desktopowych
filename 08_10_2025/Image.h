#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image {
private:
    int width;
    int height;
    int maxColorValue;
    unsigned char* data; // wskaźnik na dane pikseli (RGB)

public:
    Image();
    Image(int w, int h, int maxVal = 255);
    ~Image();

    bool loadPPM(const std::string& filename); // ASCII (P3)
    bool savePPM(const std::string& filename) const; // ASCII (P3)
    bool loadPPMBinary(const std::string& filename); // Binarny (P6)
    bool savePPMBinary(const std::string& filename) const; // Binarny (P6)

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getMaxColorValue() const { return maxColorValue; }
    unsigned char* getData() const { return data; }
};

#endif // IMAGE_H

