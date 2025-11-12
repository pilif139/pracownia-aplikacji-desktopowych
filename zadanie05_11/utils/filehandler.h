#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QUrl>
#include "image/PPMImage.h"
#include <vector>

class FileHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileHandler(QObject* parent = nullptr);
    ~FileHandler() override;

public slots:
    bool loadImage(const QString &filepath);
    bool saveImage(const QString &filepath);

signals:
    void imageLoaded(bool success, const QString &message);
    void imageSaved(bool success, const QString &message);

public: // image accessors
    int imageWidth() const;
    int imageHeight() const;
    int imageChannels() const;

    QByteArray imageRow(int row) const;
    unsigned char **imageData() const;

    void backupOriginal();
    void restoreOriginal();
    void deleteBackup();
    std::vector<uint8_t> file_backup; // store backup as a value

private:
    PPMImage *m_ppm = nullptr;
};

#endif // FILEHANDLER_H
