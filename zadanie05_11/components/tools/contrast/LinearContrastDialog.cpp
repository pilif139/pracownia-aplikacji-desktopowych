#include "LinearContrastDialog.h"
#include "ContrastTools.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>

LinearContrastDialog::LinearContrastDialog(FileHandler* file_handler, QWidget *parent)
    : QDialog(parent), fileHandler(file_handler), contrastLabel(nullptr), contrastValue(0) {
    setWindowTitle("Linear Contrast Adjustment");

    fileHandler->backupOriginal();

    auto *mainLayout = new QVBoxLayout(this);

    auto *label = new QLabel("Adjust Linear Contrast:", this);
    mainLayout->addWidget(label);

    contrastLabel = new QLabel(tr("Contrast: %1").arg(0), this);
    mainLayout->addWidget(contrastLabel);

    contrastSlider = new QSlider(Qt::Horizontal, this);
    contrastSlider->setRange(-128, 128);
    contrastSlider->setValue(0);
    mainLayout->addWidget(contrastSlider);

    auto *applyButton = new QPushButton("Apply", this);
    auto *cancelButton = new QPushButton("Cancel", this);
    mainLayout->addWidget(applyButton);
    mainLayout->addWidget(cancelButton);

    connect(applyButton, &QPushButton::clicked, this, &LinearContrastDialog::onApply);
    connect(cancelButton, &QPushButton::clicked, this, &LinearContrastDialog::onCancel);
    connect(contrastSlider, &QSlider::valueChanged, this, &LinearContrastDialog::onSliderChanged);
}

LinearContrastDialog::~LinearContrastDialog() {
    if (fileHandler && !fileHandler->file_backup.empty()) {
        fileHandler->deleteBackup();
    }
}

void LinearContrastDialog::onSliderChanged(int value) {
    fileHandler->restoreOriginal();

    contrastLabel->setText(tr("Contrast: %1").arg(value));

    contrastValue = value / 128.0;

    ContrastTools::applyLinear(fileHandler->imageData(), fileHandler->imageWidth(),
                              fileHandler->imageHeight(), contrastValue);

    emit previewUpdated();
}

void LinearContrastDialog::onApply() {
    fileHandler->deleteBackup();
    accept();
}

void LinearContrastDialog::onCancel() {
    fileHandler->restoreOriginal();
    fileHandler->deleteBackup();
    reject();
}
