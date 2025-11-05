#include "PGMImage.h"
#include <fstream>
#include <sstream>

// PGMImage::PGMImage() : width(0), height(0), data(nullptr) {}
// PGMImage::PGMImage(int w, int h) : width(w), height(h) {
//     data = new uint8_t[width * height]();
// }
// PGMImage::~PGMImage() {
//     delete[] data;
// }
//
// const int maxVal = 256;
//
// bool PGMImage::loadPGM(const std::string &filename) {
//     std::ifstream file(filename);
//     if (!file.is_open()) return false;
//     std::string line;
//     // Nagłówek
//     std::getline(file, line);
//     if (line != "P2") return false;
//     // Pomijanie komentarzy
//     do { std::getline(file, line); } while (line[0] == '#');
//     std::istringstream iss(line);
// }
