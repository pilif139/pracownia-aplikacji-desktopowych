#include "filehandler.h"
#include <QFile>

FileHandler::FileHandler(QObject *parent)
    : QObject(parent)
{
}

QString FileHandler::content() const
{
    return m_content;
}

void FileHandler::setContent(const QString &content)
{
    if (m_content != content) {
        m_content = content;
        emit contentChanged();
    }
}

bool FileHandler::saveFile(const QString &filePath)
{
    QString path = QUrl(filePath).toLocalFile();

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit fileSaved(false, "Could not open file for writing: " + path);
        return false;
    }

    QTextStream out(&file);
    out << m_content;
    file.close();

    emit fileSaved(true, "File saved successfully: " + path);
    return true;
}

bool FileHandler::loadFile(const QString &filePath)
{
    QString path = QUrl(filePath).toLocalFile();

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit fileLoaded(false, "Could not open file for reading: " + path);
        return false;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    setContent(content);
    emit fileLoaded(true, "File loaded successfully: " + path);
    return true;
}
