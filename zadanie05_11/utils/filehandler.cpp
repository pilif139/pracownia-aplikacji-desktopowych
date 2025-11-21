#include "filehandler.h"
#include <QFileInfo>
#include <QImage>
#include "image/PPMImage.h"
#include "image/PGMImage.h"
#include "image/PBMImage.h"

FileHandler::FileHandler(QObject* parent)
    : QObject(parent), currentImage(), backupImage()
{
}

FileHandler::~FileHandler()
{
}

bool FileHandler::loadImage(const QString &filepath)
{
    QString path = QFileInfo(filepath).absoluteFilePath();
    QFileInfo fi(path);
    QString ext = fi.suffix().toLower();

    Image* img = nullptr;

    if (ext == "ppm") {
        img = new PPMImage();
    } else if (ext == "pgm") {
        img = new PGMImage();
    } else if (ext == "pbm") {
        img = new PBMImage();
    } else {
        emit imageLoaded(false, "Unsupported file extension: " + ext);
        return false;
    }

    if (!img->load(path.toStdString())) {
        delete img;
        emit imageLoaded(false, "Failed to load image: " + path);
        return false;
    }

    int width = img->getWidth();
    int height = img->getHeight();
    Pixel** data = img->getData();

    if (!data || width <= 0 || height <= 0) {
        delete img;
        emit imageLoaded(false, "Invalid image data");
        return false;
    }

    bool isGrayscale = (dynamic_cast<PGMImage*>(img) != nullptr || dynamic_cast<PBMImage*>(img) != nullptr);

    currentImage = QImage(width, height, QImage::Format_RGB888);

    for (int y = 0; y < height; ++y) {
        uchar* scanLine = currentImage.scanLine(y);
        Pixel* rowData = data[y];

        if (isGrayscale) {
            for (int x = 0; x < width; ++x) {
                Pixel gray = rowData[x];
                scanLine[x * 3] = gray;     // R
                scanLine[x * 3 + 1] = gray; // G
                scanLine[x * 3 + 2] = gray; // B
            }
        } else {
            for (int x = 0; x < width * 3; ++x) {
                scanLine[x] = rowData[x];
            }
        }
    }

    delete img;
    emit imageLoaded(true, "Loaded image: " + path);
    return true;
}

bool FileHandler::saveImage(const QString &filePath) {
    if (currentImage.isNull()) {
        emit imageSaved(false, "No image data to save");
        return false;
    }

    QString path = QFileInfo(filePath).absoluteFilePath();
    QFileInfo fi(path);
    QString ext = fi.suffix().toLower();

    if (ext.isEmpty()) {
        ext = "ppm";
        path += ".ppm";
    }

    Image* img = nullptr;

    int width = currentImage.width();
    int height = currentImage.height();
    bool isGrayscale = (ext == "pgm" || ext == "pbm");

    if (ext == "ppm") {
        img = new PPMImage(width, height);
    } else if (ext == "pgm") {
        img = new PGMImage(width, height);
    } else if (ext == "pbm") {
        img = new PBMImage(width, height);
    } else {
        emit imageSaved(false, "Unsupported file extension: " + ext);
        return false;
    }

    Pixel** data = img->getData();

    for (int y = 0; y < height; ++y) {
        const uchar* scanLine = currentImage.constScanLine(y);
        Pixel* rowData = data[y];

        if (isGrayscale) {
            for (int x = 0; x < width; ++x) {
                int r = scanLine[x * 3];
                int g = scanLine[x * 3 + 1];
                int b = scanLine[x * 3 + 2];

                rowData[x] = static_cast<Pixel>(0.299 * r + 0.587 * g + 0.114 * b);
            }
        } else {
            for (int x = 0; x < width * 3; ++x) {
                rowData[x] = scanLine[x];
            }
        }
    }

    bool success = img->save(path.toStdString());
    delete img;

    if (!success) {
        emit imageSaved(false, "Failed to save image: " + path);
        return false;
    }

    emit imageSaved(true, "Saved image: " + path);
    return true;
}

void FileHandler::backupOriginal() {
    if (!currentImage.isNull()) {
        backupImage = currentImage.copy();
    }
}

void FileHandler::restoreOriginal() {
    if (!backupImage.isNull()) {
        currentImage = backupImage.copy();
    }
}

void FileHandler::deleteBackup() {
    backupImage = QImage();
}
