#include "filehandler.h"
#include <QFile>
#include <QTextStream>
#include <QUrl>
#include <QFileInfo>

#include "image/PPMImage.h"

#include <fstream>
#include <iostream>
#include <string>

FileHandler::FileHandler(QObject* parent)
    : QObject(parent)
{
}

FileHandler::~FileHandler()
{
    delete m_ppm;
    m_ppm = nullptr;
}

bool FileHandler::loadImage(const QString &filepath)
{
    std::cout<<"FileHandler::loadImage called with: "<<filepath.toStdString()<<std::endl;
    QString path = QFileInfo(filepath).absoluteFilePath();
    QFileInfo fi(path);
    QString ext = fi.suffix().toLower();
    if (ext.toStdString() != "ppm") {
        std::cout<<"Extension: "<<ext.toStdString()<<std::endl;
        emit imageLoaded(false, "Only .ppm files are supported");
        return false;
    }

    PPMImage *img = new PPMImage();
    bool ok = img->loadPPMBinary(path.toStdString());
    if (!ok) ok = img->loadPPM(path.toStdString());
    if (!ok) {
        delete img;
        emit imageLoaded(false, "Failed to load PPM image: " + path);
        return false;
    }

    // swap
    delete m_ppm;
    m_ppm = img;

    emit imageLoaded(true, "Loaded PPM: " + path);
    return true;
}

bool FileHandler::saveImage(const QString &filePath) {
    QString path = QFileInfo(filePath).absoluteFilePath();
    QFileInfo fi(path);
    QString ext = fi.suffix().toLower();
    if (ext != "ppm") {
        ext = "ppm";
        path += ".ppm";
    }

    if (!m_ppm) {
        emit imageSaved(false, "No image data to save");
        return false;
    }
    bool ok = m_ppm->savePPMBinary(path.toStdString());
    if (!ok) {
        emit imageSaved(false, "Failed to save PPM image: " + path);
        return false;
    }
    emit imageSaved(true, "Saved PPM: " + path);
    return true;
}

int FileHandler::imageWidth() const
{
    return m_ppm ? m_ppm->getWidth() : 0;
}

int FileHandler::imageHeight() const
{
    return m_ppm ? m_ppm->getHeight() : 0;
}

int FileHandler::imageChannels() const
{
    return m_ppm ? 3 : 0; // rgb 3 colors
}

QByteArray FileHandler::imageRow(int row) const
{
    if (!m_ppm) return QByteArray();
    int h = m_ppm->getHeight();
    int w = m_ppm->getWidth();
    if (row < 0 || row >= h) return QByteArray();

    unsigned char **data = m_ppm->getData();
    if (!data) return QByteArray();

    QByteArray ba;
    ba.resize(w * 3);
    for (int c = 0; c < w * 3; ++c) ba[c] = static_cast<char>(data[row][c]);
    return ba;
}

uint8_t **FileHandler::imageData() const
{
    return m_ppm ? m_ppm->getData() : nullptr;
}

void FileHandler::backupOriginal() {
    if (!m_ppm) return;
    uint8_t **data = imageData();
    if (!data) return;
    file_backup.resize(imageWidth() * imageHeight() * 3);
    for (int r = 0; r < imageHeight(); ++r) {
        std::memcpy(&file_backup[r * imageWidth() * 3], data[r], imageWidth() * 3);
    }
}

void FileHandler::restoreOriginal() {
    if (file_backup.empty()) return;
    uint8_t **data = imageData();
    if (!data) return;
    for (int r = 0; r < imageHeight(); ++r) {
        std::memcpy(data[r], &file_backup[r * imageWidth()* 3], imageWidth() * 3);
    }
}

void FileHandler::deleteBackup() {
    file_backup.clear();
}
