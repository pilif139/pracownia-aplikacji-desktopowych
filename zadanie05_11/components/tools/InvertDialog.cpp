#include "InvertDialog.h"

#include <QPushButton>
#include <QVBoxLayout>

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
    if (fileHandler && !fileHandler->file_backup.empty())
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
    uint8_t **data = fileHandler->imageData();
    if (!data) return;
    const uint f_width = fileHandler->imageWidth();
    const uint f_height = fileHandler->imageHeight();

    for (uint y = 0; y < f_height; ++y) {
        for (uint x = 0; x < f_width; ++x) {
            uint idx = x * 3;
            if (isInverted) {
                data[y][idx] = 255 - data[y][idx];         // R
                data[y][idx + 1] = 255 - data[y][idx + 1]; // G
                data[y][idx + 2] = 255 - data[y][idx + 2]; // B
            } else {
                fileHandler->restoreOriginal();
            }
        }
    }
}