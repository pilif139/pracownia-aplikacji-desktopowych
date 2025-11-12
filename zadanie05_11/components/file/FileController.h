#ifndef ZADANIE05_11_FILECONTROLLER_H
#define ZADANIE05_11_FILECONTROLLER_H

#include <QObject>
#include <QAction>
#include <QWidget>

class FileHandler;

class FileController : public QObject{
    Q_OBJECT
public:
    explicit FileController(FileHandler *fileHandler, QWidget *parent = nullptr);
    QAction *openAction() const { return m_openAction; }
    QAction *saveAction() const { return m_saveAction; }
private slots:
    void open() const;
    void save() const;
private:
    FileHandler *m_fileHandler;
    QWidget *m_parent;
    QAction *m_openAction;
    QAction *m_saveAction;
};


#endif //ZADANIE05_11_FILECONTROLLER_H