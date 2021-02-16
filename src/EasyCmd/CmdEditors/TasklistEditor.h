#ifndef TasklistEditor_H
#define TasklistEditor_H

/*******************************************************************************
** 实现tasklist命令编辑器
**
*******************************************************************************/

#include <QWidget>
#include "ICmdEditor.h"

namespace Ui {
class TasklistEditor;
}
class QStackedLayout;

class TasklistEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit TasklistEditor(QWidget *parent = 0);
    ~TasklistEditor();

    virtual bool isModified() const;
    virtual QString getCmdName();
    virtual QString getCmdString();

private slots:
    void on_checkBox_remote_system_toggled(bool checked);

    void on_checkBox_option_m_toggled(bool checked);

    void on_checkBox_option_v_toggled(bool checked);

    void on_checkBox_option_svc_toggled(bool checked);

    void on_comboBox_option_fo_currentIndexChanged(const QString &arg1);

    void on_checkBox_option_fo_toggled(bool checked);

    void on_checkBox_option_fi_toggled(bool checked);

    void on_lineEdit_option_s_textChanged(const QString &arg1);

    void on_lineEdit_option_u_textChanged(const QString &arg1);

    void on_lineEdit_option_p_textChanged(const QString &arg1);

    void on_lineEdit_option_m_textChanged(const QString &arg1);

    void on_checkBox_option_nh_toggled(bool checked);

    void on_comboBox_filterType_currentIndexChanged(int index);

private:
    void initFilters();

private:
    Ui::TasklistEditor *ui;
    QStackedLayout *m_op_layout;
    QStackedLayout *m_fiValue_layout;
};

#endif // TasklistEditor_H
