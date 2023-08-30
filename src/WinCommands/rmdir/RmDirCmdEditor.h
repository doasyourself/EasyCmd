#ifndef RmDirCmdEditor_H
#define RmDirCmdEditor_H

#include <QWidget>
#include "ICmdEditor.h"
#include "RmDirCommand.h"

namespace Ui {
class RmDirCmdEditor;
}

class RmDirCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit RmDirCmdEditor(RmDirCommand *command, QWidget *parent = 0);
    ~RmDirCmdEditor();

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);

protected:
    QString getOptions();
    bool check();
    QString getCmdString();

private slots:
    void on_lineEdit_arg_dirpath_textChanged(const QString &dirpath);

    void on_checkBox_option_d_toggled(bool checked);

    void on_btn_chooseDirpath_clicked();

    void on_chbox_option_s_toggled(bool checked);

    void on_chbox_option_q_toggled(bool checked);

    void on_chBox_option_help_toggled(bool checked);

private:
    Ui::RmDirCmdEditor *ui;
    RmDirCommand *m_command;
};

#endif // RmDirCmdEditor_H
