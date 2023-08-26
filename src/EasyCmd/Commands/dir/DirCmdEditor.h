#ifndef DirCmdEditor_H
#define DirCmdEditor_H

#include <QWidget>
#include "ICmdEditor.h"

namespace Ui {
class DirCmdEditor;
}

class DirCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit DirCmdEditor(QWidget *parent = 0);
    ~DirCmdEditor();

    virtual bool isModified() const;

    virtual QString getCmdName();

    virtual QString getCmdString();

private slots:
    void on_pushButton_arg_browserDir_clicked();

    void on_lineEdit_arg_dirpath_textChanged(const QString &dirpath);

    void on_checkBox_option_d_toggled(bool checked);

private:
    Ui::DirCmdEditor *ui;
};

#endif // DirCmdEditor_H
