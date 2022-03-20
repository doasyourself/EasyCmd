#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "MyDialog.h"

namespace Ui {
class AboutDialog;
}

class AboutDialog : public MyDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

private:
    void init();

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
