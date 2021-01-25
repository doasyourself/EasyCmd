#ifndef ABOUTUSDIALOG_H
#define ABOUTUSDIALOG_H

#include <QDialog>

namespace Ui {
class AboutUsDialog;
}

class AboutUsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutUsDialog(QWidget *parent = 0);
    ~AboutUsDialog();

private:
    Ui::AboutUsDialog *ui;
};

#endif // ABOUTUSDIALOG_H
