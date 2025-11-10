#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QtQml/qqml.h>

class FileHandler : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
public:
    explicit FileHandler(QObject* parent = nullptr);

    QString content() const;
    void setContent(const QString &content);

public slots:
    bool saveFile(const QString &filepath);
    bool loadFile(const QString &filepath);

signals:
    void contentChanged();
    void fileSaved(bool success, const QString &message);
    void fileLoaded(bool success, const QString &message);

private:
    QString m_content;
};

#endif // FILEHANDLER_H
