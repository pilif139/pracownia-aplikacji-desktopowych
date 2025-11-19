#include "ToolsManager.h"

#include "GrayscaleDialog.h"
#include "InvertDialog.h"
#include "contrast/LinearContrastDialog.h"
#include "contrast/LogContrastDialog.h"
#include "contrast/ExpContrastDialog.h"

ToolsManager::ToolsManager(FileHandler *file_handler, QWidget *parent)
    : QObject(parent), fileHandler(file_handler), parentWidget(parent) {}

void ToolsManager::populateMenu(QMenu *toolsMenu) {
    auto *gray = new QAction(tr("Desaturate Image"), this);
    connect(gray, &QAction::triggered, this, &ToolsManager::onGrayscaleSelected);
    toolsMenu->addAction(gray);

    auto *invert = new QAction(tr("Invert Colors"), this);
    connect(invert, &QAction::triggered, this, &ToolsManager::onInvertSelected);
    toolsMenu->addAction(invert);

    toolsMenu->addSeparator();

    // Create Contrast submenu
    QMenu *contrastMenu = toolsMenu->addMenu(tr("Contrast"));

    auto *linearAction = new QAction(tr("Linear"), this);
    connect(linearAction, &QAction::triggered, this, &ToolsManager::onLinearContrastSelected);
    contrastMenu->addAction(linearAction);

    auto *logAction = new QAction(tr("Logarithmic"), this);
    connect(logAction, &QAction::triggered, this, &ToolsManager::onLogContrastSelected);
    contrastMenu->addAction(logAction);

    auto *expAction = new QAction(tr("Exponential"), this);
    connect(expAction, &QAction::triggered, this, &ToolsManager::onExpContrastSelected);
    contrastMenu->addAction(expAction);
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

void ToolsManager::onLinearContrastSelected() {
    if (!fileHandler) {
        emit imageModified(false, tr("No file handler available."));
        return;
    }

    LinearContrastDialog dialog(fileHandler, parentWidget);
    connect(&dialog, &LinearContrastDialog::previewUpdated, [this]() {
        emit imageModified(true, tr("Preview updated."));
    });

    if (dialog.exec() == QDialog::Accepted) {
        emit imageModified(true, tr("Linear contrast applied successfully."));
    } else {
        emit imageModified(true, tr("Linear contrast adjustment canceled."));
    }
}

void ToolsManager::onLogContrastSelected() {
    if (!fileHandler) {
        emit imageModified(false, tr("No file handler available."));
        return;
    }

    LogContrastDialog dialog(fileHandler, parentWidget);
    connect(&dialog, &LogContrastDialog::previewUpdated, [this]() {
        emit imageModified(true, tr("Preview updated."));
    });

    if (dialog.exec() == QDialog::Accepted) {
        emit imageModified(true, tr("Logarithmic contrast applied successfully."));
    } else {
        emit imageModified(true, tr("Logarithmic contrast adjustment canceled."));
    }
}

void ToolsManager::onExpContrastSelected() {
    if (!fileHandler) {
        emit imageModified(false, tr("No file handler available."));
        return;
    }

    ExpContrastDialog dialog(fileHandler, parentWidget);
    connect(&dialog, &ExpContrastDialog::previewUpdated, [this]() {
        emit imageModified(true, tr("Preview updated."));
    });

    if (dialog.exec() == QDialog::Accepted) {
        emit imageModified(true, tr("Exponential contrast applied successfully."));
    } else {
        emit imageModified(true, tr("Exponential contrast adjustment canceled."));
    }
}
