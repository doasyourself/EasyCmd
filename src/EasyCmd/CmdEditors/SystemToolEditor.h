#ifndef SYSTEMTOOLEDITOR_H
#define SYSTEMTOOLEDITOR_H

/*******************************************************************************
** 截图工具和屏幕键盘无法启动，可能是因为权限问题，故暂不集成。
**
*******************************************************************************/

#include <QWidget>
#include "ICmdEditor.h"

namespace Ui {
class SystemToolEditor;
}

class SystemToolEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit SystemToolEditor(QWidget *parent = nullptr);
    virtual ~SystemToolEditor();

    virtual bool isModified() const;
    virtual QString getCmdString();

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

private:
    Ui::SystemToolEditor *ui;
    QString m_current_cmd;
};

#endif // SYSTEMTOOLEDITOR_H
