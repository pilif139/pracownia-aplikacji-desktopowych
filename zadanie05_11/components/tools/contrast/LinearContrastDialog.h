//
// Created by Filip on 18/11/2025.
//

#ifndef ZADANIE05_11_LINEARCONTRASTDIALOG_H
#define ZADANIE05_11_LINEARCONTRASTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSlider>

#include "../../../utils/filehandler.h"

class LinearContrastDialog : public QDialog {
    Q_OBJECT
public:
    explicit LinearContrastDialog(FileHandler* file_handler, QWidget* parent = nullptr);
    ~LinearContrastDialog() override;

signals:
    void previewUpdated();

private slots:
    void onSliderChanged(int value);
    void onApply();
    void onCancel();

private:
    FileHandler* fileHandler;
    QSlider* contrastSlider;
    QLabel* contrastLabel;
    double contrastValue;
};

#endif //ZADANIE05_11_LINEARCONTRASTDIALOG_H

