//
// Created by Filip on 11/11/2025.
//

#include "FileController.h"

#include "../../utils/filehandler.h"
#include <QFileDialog>
#include <QMessageBox>

FileController::FileController(FileHandler *fileHandler, QWidget *parent)
    : QObject(parent), m_fileHandler(fileHandler), m_parent(parent)
{
    m_openAction = new QAction(tr("&Open"), this);
    connect(m_openAction, &QAction::triggered, this, &FileController::open);

    m_saveAction = new QAction(tr("&Save"), this);
    connect(m_saveAction, &QAction::triggered, this, &FileController::save);
}

void FileController::open() const {
    QString fileName = QFileDialog::getOpenFileName(m_parent, tr("Open File"), QString(), tr("PPM images (*.ppm);;PBM images (*.pbm);;PGM images (*.pgm);;All files (*)"));
    if (fileName.isEmpty()) return;

    m_fileHandler->loadImage(fileName);
}

void FileController::save() const {
    if (!m_fileHandler->hasImage()) {
        QMessageBox::information(m_parent, tr("Save"), tr("No image to save"));
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(m_parent, tr("Save Image"), QString(),
                                                    tr("PPM Image (*.ppm);;PGM Image (*.pgm);;PBM Image (*.pbm);;All files (*)"));
    if (fileName.isEmpty()) return;
    m_fileHandler->saveImage(fileName);
}
