#ifndef IPCONFIGEDITOR_H
#define IPCONFIGEDITOR_H

/*************************************************************************
** 此命令支持无参，参考msdoc：https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/ipconfig
**
**
*************************************************************************/

#include <QWidget>
#include "ICmdEditor.h"
#include "IPConfigCommand.h"

namespace Ui {
class IPConfigCmdEditor;
}

class IPConfigCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit IPConfigCmdEditor(IPConfigCommand *command, QWidget *parent = 0);
    ~IPConfigCmdEditor();

    virtual bool isModified() const;
    virtual QString getCmdString();


private slots:
    void on_checkBox_setclassid_toggled(bool checked);

    void on_checkBox_showclassid_toggled(bool checked);

    void on_checkBox_release_toggled(bool checked);

    void on_checkBox_renew_toggled(bool checked);

    void on_checkBox_all_toggled(bool checked);

    void on_checkBox_flushdns_toggled(bool checked);

    void on_checkBox_displaydns_toggled(bool checked);

    void slotOptionChanged();

    void on_lineEdit_setclassid_textChanged(const QString &arg1);

    void on_lineEdit_showclassid_textChanged(const QString &arg1);

    void on_lineEdit_release_textChanged(const QString &arg1);

    void on_lineEdit_renew_textChanged(const QString &arg1);

    void on_lineEdit_newClassid_textChanged(const QString &arg1);

private:
    void genCmdString();

private:
    Ui::IPConfigCmdEditor *ui;
    QString m_cmd;
    IPConfigCommand *m_command;
};

#endif // IPCONFIGEDITOR_H
