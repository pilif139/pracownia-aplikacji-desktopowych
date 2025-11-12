#ifndef ZADANIE05_11_TOOLSMANAGER_H
#define ZADANIE05_11_TOOLSMANAGER_H
#include <QObject>
#include <QMenu>
#include <QWidget>

#include "../../utils/filehandler.h"


class ToolsManager : public QObject {
    Q_OBJECT
public:
    explicit ToolsManager(FileHandler *file_handler, QWidget *parent = nullptr);
    void populateMenu(QMenu *toolsMenu);

signals:
    void imageModified(bool success, const QString &message);

private slots:
    void onGrayscaleSelected();
    void onInvertSelected();

private:
    FileHandler *fileHandler;
    QWidget *parentWidget;
};


#endif //ZADANIE05_11_TOOLSMANAGER_H