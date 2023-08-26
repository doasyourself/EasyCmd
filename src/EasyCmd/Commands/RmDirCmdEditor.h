#ifndef RmDirCmdEditor_H
#define RmDirCmdEditor_H

#include <QWidget>
#include "ICmdEditor.h"

namespace Ui {
class RmDirCmdEditor;
}

class RmDirCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit RmDirCmdEditor(QWidget *parent = 0);
    ~RmDirCmdEditor();

    virtual bool isModified() const;

    virtual QString getCmdName();

    virtual QString getCmdString();

private slots:
    void on_lineEdit_arg_dirpath_textChanged(const QString &dirpath);

    void on_checkBox_option_d_toggled(bool checked);

private:
    Ui::RmDirCmdEditor *ui;
};

#endif // RmDirCmdEditor_H
