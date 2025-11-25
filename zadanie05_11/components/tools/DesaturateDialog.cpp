#include "DesaturateDialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QColor>

DesaturateDialog::DesaturateDialog(FileHandler *file_handler, QWidget *parent)
    : QDialog(parent),
      fileHandler(file_handler),
      buttonsBox(new QDialogButtonBox(this)){
    setWindowTitle(tr("Desaturate"));

    auto okBtn = new QPushButton(tr("OK"), buttonsBox);
    auto cancelBtn = new QPushButton(tr("Cancel"), buttonsBox);
    auto previewBtn = new QPushButton(tr("Preview"), buttonsBox);
    buttonsBox->addButton(okBtn, QDialogButtonBox::AcceptRole);
    buttonsBox->addButton(cancelBtn, QDialogButtonBox::RejectRole);
    buttonsBox->addButton(previewBtn, QDialogButtonBox::ActionRole);
    connect(okBtn, &QPushButton::clicked, this, &DesaturateDialog::onAccepted);
    connect(cancelBtn, &QPushButton::clicked, this, &DesaturateDialog::onRejected);
    connect(previewBtn, &QPushButton::clicked, this, [this]() {
        isDesaturated = !isDesaturated;
        onPreviewUpdated(isDesaturated);
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

DesaturateDialog::~DesaturateDialog() {
    if (fileHandler)
        fileHandler->deleteBackup();
}

void DesaturateDialog::onAccepted() {
    fileHandler->deleteBackup();
    accept();
}

void DesaturateDialog::onRejected() {
    fileHandler->restoreOriginal();
    emit previewUpdated();
    reject();
    fileHandler->deleteBackup();
}

void DesaturateDialog::onPreviewUpdated(bool isDesaturated) {
    if (!fileHandler) return;

    if (!isDesaturated) {
        fileHandler->restoreOriginal();
        emit previewUpdated();
        return;
    }

    fileHandler->restoreOriginal();
    QImage& img = fileHandler->getImage();
    if (img.isNull()) return;

    for (int y = 0; y < img.height(); ++y) {
        for (int x = 0; x < img.width(); ++x) {
            QColor color = img.pixelColor(x, y);

            int gray = static_cast<int>(0.3 * color.red() + 0.59 * color.green() + 0.11 * color.blue());

            img.setPixelColor(x, y, QColor(gray, gray, gray));
        }
    }

    emit previewUpdated();
}
