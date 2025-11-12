#include "MainWindow.h"
#include "utils/filehandler.h"
#include "components/tools/ToolsManager.h"

#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QtCore/qcoreapplication.h>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), imageLabel(new QLabel(this)), saveAction(nullptr), openAction(nullptr), scrollArea(nullptr), toolsManager(nullptr)
{
    setWindowTitle("Gimp demo");
    resize(800, 600);

    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);
    scrollArea->setAlignment(Qt::AlignCenter);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    fileHandler = new FileHandler(this);
    fileController = new FileController(fileHandler, this);
    fileMenu->addAction(fileController->openAction());
    fileMenu->addAction(fileController->saveAction());

    QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsManager = new ToolsManager(fileHandler, this);
    toolsManager->populateMenu(toolsMenu);
    connect(toolsManager, &ToolsManager::imageModified, this, &MainWindow::onImageLoaded);
    toolsMenu->setEnabled(false);
    this->toolsMenu = toolsMenu;

    fileMenu->addSeparator();
    auto quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    fileMenu->addAction(quitAction);

    connect(fileHandler, &FileHandler::imageLoaded, this, &MainWindow::onImageLoaded);
    connect(fileHandler, &FileHandler::imageSaved, this, &MainWindow::onImageSaved);
}

void MainWindow::onImageLoaded(bool success, const QString &message)
{
    if (!success) {
        if (toolsMenu) toolsMenu->setEnabled(false);
        QMessageBox::warning(this, tr("Load Failed"), message);
        return;
    }

    unsigned char **raw = fileHandler->imageData();
    int w = fileHandler->imageWidth();
    int h = fileHandler->imageHeight();
    if (!raw || w <= 0 || h <= 0) {
        if (toolsMenu) toolsMenu->setEnabled(false);
        QMessageBox::warning(this, tr("Load Failed"), tr("Invalid image data"));
        return;
    }

    QImage img(w, h, QImage::Format_RGB888);
    for (int y = 0; y < h; ++y) {
        unsigned char *row = raw[y];
        uchar *scanline = img.scanLine(y);
        for (int x = 0; x < w * 3; ++x) scanline[x] = row[x];
    }

    imageLabel->setPixmap(QPixmap::fromImage(img));
    imageLabel->adjustSize();
    statusBar()->showMessage(message, 3000);
    if (toolsMenu) toolsMenu->setEnabled(true);
}

void MainWindow::onImageSaved(bool success, const QString &message)
{
    if (!success) {
        QMessageBox::warning(this, tr("Save Failed"), message);
        return;
    }
    statusBar()->showMessage(message, 3000);
}