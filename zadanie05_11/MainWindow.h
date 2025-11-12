#pragma once

#include <QMainWindow>
#include <QAction>
#include <QStatusBar>
#include <QLabel>
#include <QScrollArea>
#include <QImage>
#include <QMenu>

#include "components/file/FileController.h"

class ToolsManager; // forward

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onImageLoaded(bool success, const QString &message);
    void onImageSaved(bool success, const QString &message);

private:
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QAction *saveAction;
    QAction *openAction;
    FileController *fileController;
    FileHandler *fileHandler;
    ToolsManager *toolsManager; // new
    QMenu *toolsMenu;
};
