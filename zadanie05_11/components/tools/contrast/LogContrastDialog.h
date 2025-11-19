//
// Created by Filip on 18/11/2025.
//

#ifndef ZADANIE05_11_LOGCONTRASTDIALOG_H
#define ZADANIE05_11_LOGCONTRASTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSlider>

#include "../../../utils/filehandler.h"

class LogContrastDialog : public QDialog {
    Q_OBJECT
public:
    explicit LogContrastDialog(FileHandler* file_handler, QWidget* parent = nullptr);
    ~LogContrastDialog() override;

signals:
    void previewUpdated();

private slots:
    void onSliderChanged(int value);
    void onApply();
    void onCancel();

private:
    FileHandler* fileHandler;
    QSlider* kSlider;
    QLabel* kLabel;
    double k;
};


#endif //ZADANIE05_11_LOGCONTRASTDIALOG_H

