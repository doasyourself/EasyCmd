#ifndef TaskkillCmdEditor_H
#define TaskkillCmdEditor_H

/*******************************************************************************
** 实现taskkill命令编辑器
** TODO:
** 1.只有在应用筛选器的情况下，/IM 切换才能使用通配符 '*'（不好处理，暂时不管）
*******************************************************************************/

#include <QWidget>
#include "ICmdEditor.h"
#include "TaskkillCommand.h"

namespace Ui {
class TaskkillCmdEditor;
}
class QStackedLayout;

class TaskkillCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit TaskkillCmdEditor(TaskkillCommand *command, QWidget *parent = 0);
    ~TaskkillCmdEditor();

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);

protected:
    QString getCmdString();

private slots:
    void on_lineEdit_option_s_textChanged(const QString &arg1);

    void on_lineEdit_option_u_textChanged(const QString &arg1);

    void on_lineEdit_option_p_textChanged(const QString &arg1);

    void on_comboBox_filterType_currentIndexChanged(int index);

    void on_groupBox_remote_system_toggled(bool arg1);

    void on_pushButton_addFilter_clicked();

    void on_pushButton_clearFilter_clicked();

    void on_spinBox_option_value_pid_valueChanged(int arg1);

    void on_lineEdit_option_value_im_textChanged(const QString &arg1);

    void on_checkBox_option_t_toggled(bool checked);

    void on_checkBox_option_f_toggled(bool checked);

    void on_radioButton_option_pid_toggled(bool checked);

    void on_radioButton_option_im_toggled(bool checked);

    void slot_checkBox_clicked();

private:
    void initFilters();/*初始化过滤器*/
    void setupFilterTypes(bool remote_system);/*加载过滤器列表*/

private:
    Ui::TaskkillCmdEditor *ui;
    TaskkillCommand *m_command;

    QStackedLayout *m_op_layout;
    QStackedLayout *m_fiValue_layout;
    QStringList m_filter_list;/*筛选器列表*/
};

#endif // TaskkillCmdEditor_H
