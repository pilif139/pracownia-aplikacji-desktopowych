#include "Image.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

Image::Image() : width(0), height(0), maxColorValue(255), data(nullptr) {}

Image::Image(int w, int h, int maxVal) : width(w), height(h), maxColorValue(maxVal) {
    data = new unsigned char[width * height * 3]();
}

Image::~Image() {
    delete[] data;
}

bool Image::loadPPM(const std::string& filename) {
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

bool Image::savePPM(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open() || !data) return false;
    file << "P3\n";
    file << width << " " << height << "\n";
    file << maxColorValue << "\n";
    for (int i = 0; i < width * height * 3; ++i) {
        file << (int)data[i] << ((i + 1) % 12 == 0 ? "\n" : " ");
    }
    return true;
}

bool Image::loadPPMBinary(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;
    std::string line;
    std::getline(file, line);
    if (line != "P6") return false;
    // Pomijanie komentarzy
    do { std::getline(file, line); } while (line[0] == '#');
    std::istringstream iss(line);
    iss >> width >> height;
    file >> maxColorValue;
    file.get(); // pominąć znak nowej linii
    delete[] data;
    data = new unsigned char[width * height * 3];
    file.read(reinterpret_cast<char*>(data), width * height * 3);
    return true;
}

bool Image::savePPMBinary(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open() || !data) return false;
    file << "P6\n";
    file << width << " " << height << "\n";
    file << maxColorValue << "\n";
    file.write(reinterpret_cast<const char*>(data), width * height * 3);
    return true;
}

