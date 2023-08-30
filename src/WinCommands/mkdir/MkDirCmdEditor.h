#ifndef MkDirCmdEditor_H
#define MkDirCmdEditor_H

#include <QWidget>
#include "ICmdEditor.h"
#include "MkDirCommand.h"

namespace Ui {
class MkDirCmdEditor;
}

class MkDirCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit MkDirCmdEditor(MkDirCommand *command, QWidget *parent = 0);
    ~MkDirCmdEditor();

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);

protected:
    QString getOptions();

    QString getCmdString();

private slots:
    void on_lineEdit_arg_dirpath_textChanged(const QString &dirpath);

    void on_checkBox_option_d_toggled(bool checked);

    void on_btn_chooseDirpath_clicked();

    void on_chbox_help_toggled(bool checked);

private:
    bool check();

private:
    Ui::MkDirCmdEditor *ui;
    MkDirCommand *m_command;
};

#endif // MkDirCmdEditor_H
