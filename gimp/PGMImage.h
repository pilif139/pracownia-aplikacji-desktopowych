#ifndef INC_08_10_2025_PGMIMAGE_H
#define INC_08_10_2025_PGMIMAGE_H
#include <cstdint>
#include <string>


class PGMImage {
    int width;
    int height;
    uint8_t* data;
public:
    PGMImage();
    PGMImage(int w, int h);
    ~PGMImage();

    bool loadPGM(const std::string& filename);
    bool savePGM(const std::string& filename) const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    uint8_t* getData() const { return data; }
};


#endif //INC_08_10_2025_PGMIMAGE_H