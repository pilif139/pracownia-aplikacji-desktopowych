#include "SaturationDialog.h"

#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

int SaturationDialog::saturateValue = 100.0;
int** SaturationDialog::lookupTable = new int*[101];

SaturationDialog::SaturationDialog(FileHandler *file_handler, QWidget *parent)
    : QDialog(parent),
      fileHandler(file_handler),
      slider(new QSlider(Qt::Horizontal, this)),
      valueLabel(new QLabel(this)),
      buttonsBox(new QDialogButtonBox(this))
{
    for (int i=0; i<101; i++) {
        lookupTable[i] = new int[256];
        for (int j=0; j<256; j++) {
            lookupTable[i][j] = -1;
        }
    }

    setWindowTitle(tr("Change saturation"));

    slider->setRange(0, 100);
    slider->setValue(saturateValue);
    slider->setMinimumWidth(200);
    valueLabel->setText(QString("%1%").arg(slider->value()));

    auto okBtn = new QPushButton(tr("OK"), buttonsBox);
    auto cancelBtn = new QPushButton(tr("Cancel"), buttonsBox);
    buttonsBox->addButton(okBtn, QDialogButtonBox::AcceptRole);
    buttonsBox->addButton(cancelBtn, QDialogButtonBox::RejectRole);
    connect(okBtn, &QPushButton::clicked, this, &SaturationDialog::onAccepted);
    connect(cancelBtn, &QPushButton::clicked, this, &SaturationDialog::onRejected);
    connect(slider, &QSlider::valueChanged, this, &SaturationDialog::onSliderChanged);

    if (fileHandler && fileHandler->imageWidth() > 0 && fileHandler->imageHeight() > 0)
        fileHandler->backupOriginal();

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

    QTimer::singleShot(0, this, [this]()
                       { if (slider) slider->setFocus(); });
}

SaturationDialog::~SaturationDialog()
{
    if (fileHandler)
        fileHandler->deleteBackup();
}

void SaturationDialog::applyFactorToHandler()
{
    if (!fileHandler)
        return;

    QImage &img = fileHandler->getImage();
    if (img.isNull()) {
        return;
    }
    int width = fileHandler->imageWidth();
    int height = fileHandler->imageHeight();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QColor color = img.pixelColor(x, y);

            const int hsv = color.hsvSaturation();
            int newSaturation;
            if (lookupTable[saturateValue][hsv] != -1) {
                newSaturation = lookupTable[saturateValue][hsv];
            } else {
                newSaturation = static_cast<int>(hsv * (saturateValue / 100.0));
                newSaturation = qBound(0, newSaturation, 255);
                lookupTable[saturateValue][hsv] = newSaturation;
            }
            if (hsv != newSaturation) {
                color.setHsv(color.hue(), newSaturation, color.value(), color.alpha());
                img.setPixelColor(x, y, color);
            }
        }
    }
}

void SaturationDialog::onSliderChanged(int value)
{
    saturateValue = value;
    valueLabel->setText(QString("%1%").arg(value));

    if (fileHandler)
        fileHandler->restoreOriginal();

    applyFactorToHandler();

    emit previewUpdated();
}

void SaturationDialog::onAccepted()
{
    accept();
}

void SaturationDialog::onRejected()
{
    if (fileHandler)
        fileHandler->restoreOriginal();
    reject();
}