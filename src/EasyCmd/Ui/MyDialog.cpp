#include "MyDialog.h"
#include <QKeyEvent>

MyDialog::MyDialog(QWidget *parent) : QDialog(parent)
{

}

void MyDialog::keyPressEvent(QKeyEvent *e)
{
    // 禁用ESC退出特性
    if (e->key() == Qt::Key_Escape)
    {
        return;
    }

    QDialog::keyPressEvent(e);
}
