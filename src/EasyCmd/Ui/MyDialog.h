#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

class MyDialog : public QDialog
{
public:
    explicit MyDialog(QWidget *parent = NULL);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
};

#endif // MYDIALOG_H
