#ifndef TRACERTCMDEDITOR_H
#define TRACERTCMDEDITOR_H

/*******************************************************************************
** tracert命令编辑器
** 微软在线文档：https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/tracert
**
********************************************************************************/

#include <QWidget>
#include "ICmdEditor.h"
#include "TracertCommand.h"

namespace Ui {
class TracertCmdEditor;
}

class TracertCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit TracertCmdEditor(TracertCommand *command, QWidget *parent = 0);
    ~TracertCmdEditor();

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);

protected:
    QString getCmdString();

private slots:
    void on_lineEdit_arg_value_targetName_textChanged(const QString &arg1);

    void on_checkBox_option_d_toggled(bool checked);

    void on_checkBox_option_h_toggled(bool checked);

    void on_checkBox_option_w_toggled(bool checked);

    void on_checkBox_option_R_toggled(bool checked);

    void on_checkBox_option_S_toggled(bool checked);

    void on_radioButton_option_ipv4_toggled(bool checked);

    void on_radioButton_option_ipv6_toggled(bool checked);

    void on_lineEdit_option_value_S_textChanged(const QString &arg1);

    void on_spinBox_option_value_w_valueChanged(int arg1);

    void on_spinBox_option_value_h_valueChanged(int arg1);

    void on_checkBox_option_j_toggled(bool checked);

    void on_lineEdit_option_value_j_textChanged(const QString &arg1);

private:
    Ui::TracertCmdEditor *ui;
    TracertCommand *m_command;
};

#endif // TRACERTCMDEDITOR_H
