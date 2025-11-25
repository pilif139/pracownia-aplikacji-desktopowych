#ifndef DESATURATEDIALOG_H
#define DESATURATEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include "../../utils/filehandler.h"

class DesaturateDialog : public QDialog {
    Q_OBJECT
public:
    explicit DesaturateDialog(FileHandler *file_handler, QWidget *parent = nullptr);
    ~DesaturateDialog() override;

signals:
    void previewUpdated();

private slots:
    void onPreviewUpdated(bool isDesaturated);
    void onAccepted();
    void onRejected();

private:
    FileHandler *fileHandler;
    QDialogButtonBox *buttonsBox;
    bool isDesaturated = false;
};

#endif // DESATURATEDIALOG_H