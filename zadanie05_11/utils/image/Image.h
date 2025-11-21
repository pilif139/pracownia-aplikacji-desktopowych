//
// Created by Filip on 19/11/2025.
//

#ifndef ZADANIE05_11_IMAGE_H
#define ZADANIE05_11_IMAGE_H

#include <string>
#define ColorValue uint8_t

class Image {
protected:
    unsigned int width = 0;
    unsigned int height = 0;
    ColorValue **data = nullptr;

    Image() = default;
    Image(unsigned int w, unsigned int h) : width(w), height(h), data(nullptr) {}

public:
    virtual ~Image() = default;

    // Pure virtual methods that derived classes must implement
    virtual bool load(const std::string& filename) = 0;
    virtual bool save(const std::string& filename) const = 0;

    ColorValue** getData() const { return data; }
    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }
};


#endif //ZADANIE05_11_IMAGE_H