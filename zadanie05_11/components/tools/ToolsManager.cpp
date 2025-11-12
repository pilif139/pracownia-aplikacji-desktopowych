#include "ToolsManager.h"

#include "GrayscaleDialog.h"
#include "InvertDialog.h"

ToolsManager::ToolsManager(FileHandler *file_handler, QWidget *parent)
    : QObject(parent), fileHandler(file_handler), parentWidget(parent) {}

void ToolsManager::populateMenu(QMenu *toolsMenu) {
    auto *gray = new QAction(tr("Desaturate Image"), this);
    connect(gray, &QAction::triggered, this, &ToolsManager::onGrayscaleSelected);
    toolsMenu->addAction(gray);
    auto *invert = new QAction(tr("Invert Colors"), this);
    connect(invert, &QAction::triggered, this, &ToolsManager::onInvertSelected);
    toolsMenu->addAction(invert);
}

void ToolsManager::onGrayscaleSelected() {
    if (!fileHandler) {
        emit imageModified(false, tr("No file handler available."));
        return;
    }

    GrayscaleDialog dialog(fileHandler, parentWidget);
    connect(&dialog, &GrayscaleDialog::previewUpdated, [this]() {
        emit imageModified(true, tr("Image preview updated."));
    });

    if (dialog.exec() == QDialog::Accepted) {
        emit imageModified(true, tr("Image desaturated successfully."));
    } else {
        emit imageModified(true, tr("Image desaturation canceled."));
    }
}

void ToolsManager::onInvertSelected() {
    if (!fileHandler) {
        emit imageModified(false, tr("No file handler available."));
        return;
    }
    InvertDialog dialog(fileHandler, parentWidget);
    connect(&dialog, &InvertDialog::previewUpdated, [this]() {
        emit imageModified(true, tr("Image preview updated."));
    });

    if (dialog.exec() == QDialog::Accepted) {
        emit imageModified(true, tr("Image colors inverted successfully."));
    } else {
        emit imageModified(true, tr("Image color inversion canceled."));
    }
}