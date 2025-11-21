#include "InvertDialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QColor>

InvertDialog::InvertDialog(FileHandler *file_handler, QWidget *parent)
    : QDialog(parent),
      fileHandler(file_handler),
      buttonsBox(new QDialogButtonBox(this)){
    setWindowTitle(tr("Invert Colors"));

    auto okBtn = new QPushButton(tr("OK"), buttonsBox);
    auto cancelBtn = new QPushButton(tr("Cancel"), buttonsBox);
    auto previewBtn = new QPushButton(tr("Preview"), buttonsBox);
    buttonsBox->addButton(okBtn, QDialogButtonBox::AcceptRole);
    buttonsBox->addButton(cancelBtn, QDialogButtonBox::RejectRole);
    buttonsBox->addButton(previewBtn, QDialogButtonBox::ActionRole);
    connect(okBtn, &QPushButton::clicked, this, &InvertDialog::onAccepted);
    connect(cancelBtn, &QPushButton::clicked, this, &InvertDialog::onRejected);
    connect(previewBtn, &QPushButton::clicked, this, [this]() {
        isInverted = !isInverted;
        onPreviewUpdated(isInverted);
        emit previewUpdated();
    });

    if (fileHandler && fileHandler->imageWidth() > 0 && fileHandler->imageHeight() > 0)
        fileHandler->backupOriginal();

    auto *topLay = new QVBoxLayout(this);
    topLay->addWidget(buttonsBox);

    okBtn->setFocusPolicy(Qt::NoFocus);
    okBtn->setAutoDefault(false);
    okBtn->setDefault(false);

    cancelBtn->setFocusPolicy(Qt::NoFocus);
}

InvertDialog::~InvertDialog() {
    if (fileHandler)
        fileHandler->deleteBackup();
}

void InvertDialog::onAccepted() {
    fileHandler->deleteBackup();
    accept();
}

void InvertDialog::onRejected() {
    fileHandler->restoreOriginal();
    emit previewUpdated();
    reject();
    fileHandler->deleteBackup();
}

void InvertDialog::onPreviewUpdated(bool isInverted) {
    if (!fileHandler) return;

    if (!isInverted) {
        fileHandler->restoreOriginal();
        emit previewUpdated();
        return;
    }

    fileHandler->restoreOriginal();
    QImage& img = fileHandler->getImage();
    if (img.isNull()) return;

    // Invert colors using QColor and pixel()/setPixel()
    for (int y = 0; y < img.height(); ++y) {
        for (int x = 0; x < img.width(); ++x) {
            QColor color = img.pixelColor(x, y);
            color.setRgb(255 - color.red(), 255 - color.green(), 255 - color.blue());
            img.setPixelColor(x, y, color);
        }
    }

    emit previewUpdated();
}