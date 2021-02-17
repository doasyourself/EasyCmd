#ifndef TaskkillEditor_H
#define TaskkillEditor_H

/*******************************************************************************
** 实现tasklist命令编辑器
**
*******************************************************************************/

#include <QWidget>
#include "ICmdEditor.h"

namespace Ui {
class TaskkillEditor;
}
class QStackedLayout;

class TaskkillEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit TaskkillEditor(QWidget *parent = 0);
    ~TaskkillEditor();

    virtual bool isModified() const;
    virtual QString getCmdName();
    virtual QString getCmdString();

private slots:
    void on_comboBox_option_fo_currentIndexChanged(const QString &arg1);

    void on_checkBox_option_fo_toggled(bool checked);

    void on_lineEdit_option_s_textChanged(const QString &arg1);

    void on_lineEdit_option_u_textChanged(const QString &arg1);

    void on_lineEdit_option_p_textChanged(const QString &arg1);

    void on_checkBox_option_nh_toggled(bool checked);

    void on_comboBox_filterType_currentIndexChanged(int index);

    void on_groupBox_remote_system_toggled(bool arg1);

    void on_groupBox_filter_toggled(bool arg1);

private:
    void initFilters();/*初始化过滤器*/
    void setupFilterTypes(bool remote_system);/*加载过滤器列表*/

private:
    Ui::TaskkillEditor *ui;
    QStackedLayout *m_op_layout;
    QStackedLayout *m_fiValue_layout;
};

#endif // TaskkillEditor_H
