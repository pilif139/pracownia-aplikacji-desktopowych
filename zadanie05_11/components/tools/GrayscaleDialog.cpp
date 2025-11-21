#include "GrayscaleDialog.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTimer>
#include <QColor>
#include <cmath>

GrayscaleDialog::GrayscaleDialog(FileHandler *file_handler, QWidget *parent)
    : QDialog(parent),
        lookupTable{},
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
    if (fileHandler) fileHandler->deleteBackup();
}

void GrayscaleDialog::applyFactorToHandler(double factor) {
    if (!fileHandler) return;

    fileHandler->restoreOriginal();
    QImage& img = fileHandler->getImage();
    if (img.isNull()) return;

    for (int y = 0; y < img.height(); ++y) {
        for (int x = 0; x < img.width(); ++x) {
            QColor color = img.pixelColor(x, y);
            // Calculate luminance using ITU-R BT.709
            double L = 0.3 * color.red() + 0.6 * color.green() + 0.1 * color.blue();

            // Apply desaturation factor
            int nr = qBound(0, static_cast<int>(std::lround(color.red() + factor * (L - color.red()))), 255);
            int ng = qBound(0, static_cast<int>(std::lround(color.green() + factor * (L - color.green()))), 255);
            int nb = qBound(0, static_cast<int>(std::lround(color.blue() + factor * (L - color.blue()))), 255);

            img.setPixelColor(x, y, QColor(nr, ng, nb));
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
