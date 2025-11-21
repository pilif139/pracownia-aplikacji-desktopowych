#ifndef ZADANIE05_11_GRAYSCALEDIALOG_H
#define ZADANIE05_11_GRAYSCALEDIALOG_H
#include <QLabel>
#include <QtWidgets/qdialog.h>
#include <QSlider>
#include <QDialogButtonBox>

#include "../../utils/filehandler.h"
#include "../../utils/image/Image.h"


class GrayscaleDialog : public QDialog{
    Q_OBJECT
public:
    explicit GrayscaleDialog(FileHandler *file_handler,QWidget *parent=nullptr);
    double desaturationValue() const;
    ~GrayscaleDialog() override;

signals:
    void previewUpdated();

private slots:
    void onSliderChanged(int value);
    void onAccepted();
    void onRejected();

private:
    void applyFactorToHandler(double factor);

    FileHandler *fileHandler;
    QSlider *slider;
    QLabel *valueLabel;
    QDialogButtonBox *buttonsBox;
};


#endif //ZADANIE05_11_GRAYSCALEDIALOG_H