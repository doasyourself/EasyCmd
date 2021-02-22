#ifndef CDCMDEDITOR_H
#define CDCMDEDITOR_H

#include <QWidget>
#include "ICmdEditor.h"

namespace Ui {
class CdCmdEditor;
}

class CdCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit CdCmdEditor(QWidget *parent = 0);
    ~CdCmdEditor();

    virtual bool isModified() const;

    virtual QString getCmdName();

    virtual QString getCmdString();

private slots:
    void on_pushButton_arg_browserDir_clicked();

    void on_lineEdit_arg_dirpath_textChanged(const QString &dirpath);

    void on_checkBox_option_d_toggled(bool checked);

private:
    Ui::CdCmdEditor *ui;
};

#endif // CDCMDEDITOR_H
