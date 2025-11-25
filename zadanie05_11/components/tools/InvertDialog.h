#ifndef ZADANIE05_11_NEGATIVEDIALOG_H
#define ZADANIE05_11_NEGATIVEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include "../../utils/filehandler.h"

class InvertDialog : public QDialog {
    Q_OBJECT
public:
    explicit InvertDialog(FileHandler *file_handler, QWidget *parent = nullptr);
    ~InvertDialog() override;

signals:
    void previewUpdated();

private slots:
    void onPreviewUpdated(bool isInverted);
    void onAccepted();
    void onRejected();

private:
    FileHandler *fileHandler;
    QDialogButtonBox *buttonsBox;
    bool isInverted = false;
};


#endif //ZADANIE05_11_NEGATIVEDIALOG_H
