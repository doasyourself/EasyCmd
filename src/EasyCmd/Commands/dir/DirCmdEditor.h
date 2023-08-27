#ifndef DirCmdEditor_H
#define DirCmdEditor_H

/*******************************************************************************
** 参考：
** - https://www.2brightsparks.com/resources/articles/understanding-file-attributes.html
** - https://learn.microsoft.com/zh-cn/windows/win32/fileio/file-attribute-constants
**
**
*******************************************************************************/

#include <QWidget>
#include "ICmdEditor.h"
#include "DirCommand.h"

namespace Ui {
class DirCmdEditor;
}

class DirCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit DirCmdEditor(DirCommand *command, QWidget *parent = 0);
    ~DirCmdEditor();

    virtual bool isModified() const;

    virtual QString getCmdString();

private slots:
    void on_lineEdit_arg_dirOrFilepath_textChanged(const QString &dirpath);

    void on_btn_chooseDirpath_clicked();

    void on_btn_chooseFilepath_clicked();

    void on_btn_resetOptions_clicked();

private:
    Ui::DirCmdEditor *ui;
    DirCommand *m_command;
};

#endif // DirCmdEditor_H
