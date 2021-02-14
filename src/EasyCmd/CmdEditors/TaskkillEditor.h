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

class TaskkillEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit TaskkillEditor(QWidget *parent = 0);
    ~TaskkillEditor();

    virtual bool isModified() const;
    virtual QString getCmdName();
    virtual QString getCmdString();

private:
    Ui::TaskkillEditor *ui;
    QString m_cmd;
};

#endif // TaskkillEditor_H
