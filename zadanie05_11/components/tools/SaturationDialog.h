#ifndef ZADANIE05_11_SATURATIONDIALOG_H
#define ZADANIE05_11_SATURATIONDIALOG_H
#include <QLabel>
#include <QSlider>

#include "DesaturateDialog.h"


class SaturationDialog: public QDialog {
    Q_OBJECT
public:
    explicit SaturationDialog(FileHandler *file_handler, QWidget *parent);
    ~SaturationDialog() override;
    static int saturateValue;
    static int** lookupTable;
signals:
    void previewUpdated();
private slots:
    void onSliderChanged(int value);
    void onAccepted();
    void onRejected();
private:
    void applyFactorToHandler();
    FileHandler *fileHandler;
    QSlider *slider;
    QLabel *valueLabel;
    QDialogButtonBox *buttonsBox;
};


#endif //ZADANIE05_11_SATURATIONDIALOG_H