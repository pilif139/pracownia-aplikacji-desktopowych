#include "ExpContrastDialog.h"
#include "ContrastTools.h"

#include <QPushButton>
#include <QVBoxLayout>

ExpContrastDialog::ExpContrastDialog(FileHandler* file_handler, QWidget *parent)
    : QDialog(parent), fileHandler(file_handler), kLabel(nullptr), k(1.0) {
    setWindowTitle("Exponential Contrast Adjustment");

    fileHandler->backupOriginal();

    auto *mainLayout = new QVBoxLayout(this);

    auto *label = new QLabel("Adjust Exponential Parameter:", this);
    mainLayout->addWidget(label);

    kLabel = new QLabel(tr("k: %1").arg(1.00, 0, 'f', 2), this);
    mainLayout->addWidget(kLabel);

    kSlider = new QSlider(Qt::Horizontal, this);
    kSlider->setRange(1, 1000); // k in [0.01, 10.0] scaled by 100
    kSlider->setValue(100); // default k = 1.0
    mainLayout->addWidget(kSlider);

    auto *applyButton = new QPushButton("Apply", this);
    auto *cancelButton = new QPushButton("Cancel", this);
    mainLayout->addWidget(applyButton);
    mainLayout->addWidget(cancelButton);

    connect(applyButton, &QPushButton::clicked, this, &ExpContrastDialog::onApply);
    connect(cancelButton, &QPushButton::clicked, this, &ExpContrastDialog::onCancel);
    connect(kSlider, &QSlider::valueChanged, this, &ExpContrastDialog::onSliderChanged);
}

ExpContrastDialog::~ExpContrastDialog() {
    if (fileHandler) {
        fileHandler->deleteBackup();
    }
}

void ExpContrastDialog::onSliderChanged(int value) {
    fileHandler->restoreOriginal();

    k = value / 100.0; // Convert to [0.01, 10.0]
    kLabel->setText(tr("k: %1").arg(k, 0, 'f', 2));

    ContrastTools::applyExponential(fileHandler->getImage(), k);

    emit previewUpdated();
}

void ExpContrastDialog::onApply() {
    fileHandler->deleteBackup();
    accept();
}

void ExpContrastDialog::onCancel() {
    fileHandler->restoreOriginal();
    fileHandler->deleteBackup();
    reject();
}

