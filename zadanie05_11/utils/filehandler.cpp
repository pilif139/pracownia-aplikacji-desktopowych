#include "filehandler.h"
#include <QFileInfo>
#include <QImage>
#include <fstream>
#include "image/PPMImage.h"
#include "image/PGMImage.h"
#include "image/PBMImage.h"
#include "image/Image.h"

FileHandler::FileHandler(QObject *parent)
    : QObject(parent), currentImage(), backupImage()
{
}

FileHandler::~FileHandler()
{
}

bool FileHandler::isAsciiFormat(const QString &filepath)
{
    std::ifstream file(filepath.toStdString());
    if (!file.is_open()) return false;

    std::string magicNumber;
    file >> magicNumber;

    // ASCII P1, P2, P3
    // Binarka P4 , P5, P6
    if (magicNumber == "P1" || magicNumber == "P2" || magicNumber == "P3") {
        return true;
    }
    return false;
}

bool FileHandler::loadImage(const QString &filepath)
{
    QString path = QFileInfo(filepath).absoluteFilePath();
    QFileInfo fi(path);
    QString ext = fi.suffix().toLower();

    Image *img = nullptr;

    if (ext == "ppm")
    {
        img = new PPMImage();
    }
    else if (ext == "pgm")
    {
        img = new PGMImage();
    }
    else if (ext == "pbm")
    {
        img = new PBMImage();
    }
    else
    {
        emit imageLoaded(false, "Unsupported file extension: " + ext);
        return false;
    }

    bool isAscii = isAsciiFormat(path);
    bool loadSuccess = false;

    if (isAscii) {
        loadSuccess = img->loadAscii(path.toStdString());
    } else {
        loadSuccess = img->loadBinary(path.toStdString());
    }

    if (!loadSuccess)
    {
        delete img;
        emit imageLoaded(false, "Failed to load image: " + path);
        return false;
    }

    int width = img->getWidth();
    int height = img->getHeight();
    ColorValue **data = img->getData();

    if (!data || width <= 0 || height <= 0)
    {
        delete img;
        emit imageLoaded(false, "Invalid image data");
        return false;
    }

    bool isGrayscale = (dynamic_cast<PGMImage *>(img) != nullptr || dynamic_cast<PBMImage *>(img) != nullptr);

    currentImage = QImage(width, height, QImage::Format_RGB888);

    for (int y = 0; y < height; ++y)
    {
        uchar *scanLine = currentImage.scanLine(y);
        ColorValue *rowData = data[y];

        if (isGrayscale)
        {
            for (int x = 0; x < width; ++x)
            {
                ColorValue gray = rowData[x];
                scanLine[x * 3] = gray;     // R
                scanLine[x * 3 + 1] = gray; // G
                scanLine[x * 3 + 2] = gray; // B
            }
        }
        else
        {
            for (int x = 0; x < width * 3; ++x)
            {
                scanLine[x] = rowData[x];
            }
        }
    }

    delete img;
    emit imageLoaded(true, "Loaded image: " + path);
    return true;
}

bool FileHandler::saveImage(const QString &filePath, ImageFormat format)
{
    if (currentImage.isNull())
    {
        emit imageSaved(false, "No image data to save");
        return false;
    }

    QString path = QFileInfo(filePath).absoluteFilePath();
    QFileInfo fi(path);
    QString ext = fi.suffix().toLower();

    if (ext.isEmpty())
    {
        ext = "ppm";
        path += ".ppm";
    }

    Image *img = nullptr;

    int width = currentImage.width();
    int height = currentImage.height();
    bool isGrayscale = (ext == "pgm" || ext == "pbm");

    if (ext == "ppm")
    {
        img = new PPMImage(width, height);
    }
    else if (ext == "pgm")
    {
        img = new PGMImage(width, height);
    }
    else if (ext == "pbm")
    {
        img = new PBMImage(width, height);
    }
    else
    {
        emit imageSaved(false, "Unsupported file extension: " + ext);
        return false;
    }

    ColorValue **data = img->getData();

    for (int y = 0; y < height; ++y)
    {
        const uchar *scanLine = currentImage.constScanLine(y);
        ColorValue *rowData = data[y];

        if (isGrayscale)
        {
            for (int x = 0; x < width; ++x)
            {
                int r = scanLine[x * 3];
                int g = scanLine[x * 3 + 1];
                int b = scanLine[x * 3 + 2];

                rowData[x] = static_cast<ColorValue>(0.299 * r + 0.587 * g + 0.114 * b);
            }
        }
        else
        {
            for (int x = 0; x < width * 3; ++x)
            {
                rowData[x] = scanLine[x];
            }
        }
    }

    bool saveAsAscii = false;
    if (format == ImageFormat::Auto) {
        saveAsAscii = QFileInfo(path).exists() ? isAsciiFormat(path) : false;
    } else if (format == ImageFormat::Ascii) {
        saveAsAscii = true;
    } else {
        saveAsAscii = false;
    }

    bool success = false;
    if (saveAsAscii) {
        success = img->saveAscii(path.toStdString());
    } else {
        success = img->saveBinary(path.toStdString());
    }

    delete img;

    if (!success)
    {
        emit imageSaved(false, "Failed to save image: " + path);
        return false;
    }

    emit imageSaved(true, "Saved image: " + path);
    return true;
}

void FileHandler::backupOriginal()
{
    if (!currentImage.isNull())
    {
        backupImage = currentImage.copy();
    }
}

void FileHandler::restoreOriginal()
{
    if (!backupImage.isNull())
    {
        currentImage = backupImage.copy();
    }
}

void FileHandler::deleteBackup()
{
    backupImage = QImage();
}
