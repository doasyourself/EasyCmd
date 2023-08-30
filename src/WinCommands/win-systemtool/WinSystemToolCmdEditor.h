#ifndef SYSTEMTOOLEDITOR_H
#define SYSTEMTOOLEDITOR_H

/*******************************************************************************
** 截图工具和屏幕键盘无法启动，可能是因为权限问题，故暂不集成。
**
*******************************************************************************/

#include <QWidget>
#include "ICmdEditor.h"
#include "WinSystemToolCommand.h"

namespace Ui {
class WinSystemToolCmdEditor;
}

class WinSystemToolCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit WinSystemToolCmdEditor(WinSystemToolCommand *command, QWidget *parent = nullptr);
    virtual ~WinSystemToolCmdEditor();

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);

protected:
    QString getCmdString();

private slots:
    void on_radioButton_servicemsc_clicked();

    void on_radioButton_notepad_clicked();

    void on_radioButton_cleanmgr_clicked();

    void on_radioButton_compmgmtmsc_clicked();

    void on_radioButton_devmgmtmsc_clicked();

    void on_radioButton_regedt32_clicked();

    void on_radioButton_write_clicked();

    void on_radioButton_mspaint_clicked();

    void on_radioButton_taskmgr_clicked();

    void on_radioButton_charmap_clicked();

    void on_radioButton_magnify_clicked();

    void on_radioButton_mstsc_clicked();

    void on_radioButton_dxdiag_clicked();

    void on_radioButton_controlexe_clicked();

    void on_radioButton_calc_clicked();

    void on_radioButton_explorer_clicked();

    void on_radioButton_systeminfo_toggled(bool checked);

private:
    Ui::WinSystemToolCmdEditor *ui;
    WinSystemToolCommand *m_command;

    QString m_current_cmd;
};

#endif // SYSTEMTOOLEDITOR_H
