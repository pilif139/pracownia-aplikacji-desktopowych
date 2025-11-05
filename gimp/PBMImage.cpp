#include "PBMImage.h"

#include <fstream>
#include <sstream>

PBMImage::PBMImage() : width(0), height(0), data(nullptr) {}
PBMImage::PBMImage(int w, int h) : width(w), height(h) {
    data = new bool*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new bool[width]();
    }
}
PBMImage::~PBMImage() {
    delete[] data;
}

bool PBMImage::loadPBM(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string line;
    std::getline(file, line);
    if (line != "P1") return false;
    do { std::getline(file, line); } while (line[0] == '#');
    std::istringstream iss(line);
    iss >> width >> height;
    delete[] data;
    data = new bool*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new bool[width]();
    }
    std::string val;
    int i = 0, j = 0;
    while (file >> val) {
        data[i][j] = (val == "1");
        if (++j == width) {
            j = 0;
            ++i;
        }
    }
    return true;
};

bool PBMImage::savePBM(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open() || !data) return false;
    file << "P1\n";
    file << width << " " << height << "\n";
    for (int i = 0; i < height; ++i) {
        for (int j=0; j < width; ++j) {
            file << (data[i][j] ? "1 " : "0 ");
        }
    }
    return true;
}