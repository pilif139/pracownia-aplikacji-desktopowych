#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QImage>
#include <QtGui/QImage>

enum class ImageFormat {
    Auto,
    Binary,
    Ascii
};

class FileHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileHandler(QObject* parent = nullptr);
    ~FileHandler() override;

public slots:
    bool loadImage(const QString &filepath);
    bool saveImage(const QString &filepath, ImageFormat format = ImageFormat::Auto);

signals:
    void imageLoaded(bool success, const QString &message);
    void imageSaved(bool success, const QString &message);

public: // image accessors
    QImage& getImage() { return currentImage; }
    const QImage& getImage() const { return currentImage; }

    int imageWidth() const { return currentImage.width(); }
    int imageHeight() const { return currentImage.height(); }
    bool hasImage() const { return !currentImage.isNull(); }

    void backupOriginal();
    void restoreOriginal();
    void deleteBackup();

private:
    QImage currentImage;
    QImage backupImage;

    bool isAsciiFormat(const QString &filepath);
};

#endif // FILEHANDLER_H