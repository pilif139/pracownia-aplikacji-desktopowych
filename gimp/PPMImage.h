#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class PPMImage
{
private:
    int width;
    int height;
    int maxColorValue;
    unsigned char *data; // wskaźnik na dane pikseli (RGB)

public:
    PPMImage();
    PPMImage(int w, int h, int maxVal = 255);
    ~PPMImage();

    bool loadPPM(const std::string &filename);
    bool savePPM(const std::string &filename) const;
    bool loadPPMBinary(const std::string &filename);
    bool savePPMBinary(const std::string &filename) const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getMaxColorValue() const { return maxColorValue; }
    unsigned char *getData() const { return data; }
};

#endif // IMAGE_H
