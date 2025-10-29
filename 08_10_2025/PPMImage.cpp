#include "PPMImage.h"
#include <fstream>
#include <sstream>

PPMImage::PPMImage() : width(0), height(0), maxColorValue(255), data(nullptr) {}

PPMImage::PPMImage(int w, int h, int maxVal) : width(w), height(h), maxColorValue(maxVal) {
    data = new unsigned char[width * height * 3]();
}

PPMImage::~PPMImage() {
    delete[] data;
}

bool PPMImage::loadPPM(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string line;
    // Nagłówek
    std::getline(file, line);
    if (line != "P3") return false;
    // Pomijanie komentarzy
    do { std::getline(file, line); } while (line[0] == '#');
    std::istringstream iss(line);
    iss >> width >> height;
    file >> maxColorValue;
    data = new unsigned char[width * height * 3];
    int val, i = 0;
    while (file >> val) {
        data[i++] = static_cast<unsigned char>(val);
    }
    return true;
}

bool PPMImage::savePPM(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open() || !data) return false;
    file << "P3\n";
    file << width << " " << height << "\n";
    file << maxColorValue << "\n";
    for (int i = 0; i < width * height * 3; ++i) {
        file << static_cast<int>(data[i]) << ((i + 1) % width == 0 ? "\n" : " ");
    }
    return true;
}

bool PPMImage::loadPPMBinary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    std::string line;
    std::getline(file, line);
    if (line != "P6") return false;
    do { std::getline(file, line); } while (line[0] == '#');
    std::istringstream iss(line);
    iss >> width >> height;
    file >> maxColorValue;
    file.get();
    delete[] data;
    data = new unsigned char[width * height * 3];
    file.read(reinterpret_cast<char*>(data), width * height * 3);
    return true;
}

bool PPMImage::savePPMBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open() || !data) return false;
    file << "P6\n";
    file << width << " " << height << "\n";
    file << maxColorValue << "\n";
    file.write(reinterpret_cast<const char*>(data), width * height * 3);
    return true;
}

