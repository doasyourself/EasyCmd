#ifndef CDCMDEDITOR_H
#define CDCMDEDITOR_H

#include <QWidget>
#include "ICmdEditor.h"
#include "CdCommand.h"

namespace Ui {
class CdCmdEditor;
}

class CdCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit CdCmdEditor(CdCommand *command, QWidget *parent = 0);
    ~CdCmdEditor();

    virtual bool isModified() const;

    virtual QString getCmdString();

private slots:
    // 选择路径按钮响应
    void on_pushButton_selectpath_clicked();

    // 目录文件路径改变事件响应
    void on_lineEdit_dirfilepath_textChanged(const QString &dirfilepath);

    // 选项-d切换响应
    void on_checkBox_option_d_toggled(bool checked);

    void on_rbtn_localDirpath_toggled(bool checked);

    void on_rbtn_relativePath_toggled(bool checked);

private:
    Ui::CdCmdEditor *ui;
    CdCommand *m_command;
};

#endif // CDCMDEDITOR_H
