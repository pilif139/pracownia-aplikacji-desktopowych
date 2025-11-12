#include "GrayscaleDialog.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTimer>
#include <cmath>

GrayscaleDialog::GrayscaleDialog(FileHandler *file_handler, QWidget *parent)
    : QDialog(parent),
        fileHandler(file_handler),
        slider(new QSlider(Qt::Horizontal, this)),
        valueLabel(new QLabel(this)),
        buttonsBox(new QDialogButtonBox(this)){
    setWindowTitle(tr("Desaturate Image"));

    slider->setRange(0, 100);
    slider->setValue(0);
    slider->setMinimumWidth(200);
    valueLabel->setText(QString("%1%").arg(slider->value()));

    auto okBtn = new QPushButton(tr("OK"), buttonsBox);
    auto cancelBtn = new QPushButton(tr("Cancel"), buttonsBox);
    buttonsBox->addButton(okBtn, QDialogButtonBox::AcceptRole);
    buttonsBox->addButton(cancelBtn, QDialogButtonBox::RejectRole);
    connect(okBtn, &QPushButton::clicked, this, &GrayscaleDialog::onAccepted);
    connect(cancelBtn, &QPushButton::clicked, this, &GrayscaleDialog::onRejected);
    connect(slider, &QSlider::valueChanged, this, &GrayscaleDialog::onSliderChanged);


    if (fileHandler && fileHandler->imageWidth() > 0 && fileHandler->imageHeight() > 0) fileHandler->backupOriginal();


    auto *topLay = new QVBoxLayout(this);
    auto *row = new QHBoxLayout();
    row->addWidget(slider);
    row->addWidget(valueLabel);
    topLay->addLayout(row);
    topLay->addWidget(buttonsBox);

    okBtn->setFocusPolicy(Qt::NoFocus);
    okBtn->setAutoDefault(false);
    okBtn->setDefault(false);

    cancelBtn->setFocusPolicy(Qt::NoFocus);

     QTimer::singleShot(0, this, [this]() { if (slider) slider->setFocus(); });
}
GrayscaleDialog::~GrayscaleDialog() {
    if (fileHandler && !fileHandler->file_backup.empty()) fileHandler->deleteBackup();
}

void GrayscaleDialog::applyFactorToHandler(double factor) {
    if (!fileHandler) return;
    if (fileHandler->file_backup.empty()) return;
     uint8_t **data = fileHandler->imageData();
     if (!data) return;
     const uint f_width = fileHandler->imageWidth();
     const uint f_height = fileHandler->imageHeight();

     for (int y = 0; y < f_height; ++y) {
         unsigned char *rowDst = data[y];
         const uint8_t *rowSrc = fileHandler->file_backup.data() + (y * f_width * 3);
         for (int x = 0; x < f_width; ++x) {
            int idx = x * 3;
            auto r = static_cast<double>(rowSrc[idx + 0]);
            auto g = static_cast<double>(rowSrc[idx + 1]);
            auto b = static_cast<double>(rowSrc[idx + 2]);
            double L = 0.3 * r + 0.6 * g + 0.1 * b;
            int nr = static_cast<int>(std::lround(r + factor * (L - r)));
            int ng = static_cast<int>(std::lround(g + factor * (L - g)));
            int nb = static_cast<int>(std::lround(b + factor * (L - b)));
            rowDst[idx + 0] = static_cast<unsigned char>(qBound(0, nr, 255));
            rowDst[idx + 1] = static_cast<unsigned char>(qBound(0, ng, 255));
            rowDst[idx + 2] = static_cast<unsigned char>(qBound(0, nb, 255));
        }
    }
    emit previewUpdated();
}

void GrayscaleDialog::onSliderChanged(int value) {
    valueLabel->setText(tr("%1\%").arg(value));
    double factor = value / 100.0;
    applyFactorToHandler(factor);
}

void GrayscaleDialog::onAccepted() {
    fileHandler->deleteBackup();
    accept();
}

void GrayscaleDialog::onRejected() {
    fileHandler->restoreOriginal();
    emit previewUpdated();
    fileHandler->deleteBackup();
    reject();
}

double GrayscaleDialog::desaturationValue() const {
    return slider ? (slider->value() / 100.0) : 0.0;
}
