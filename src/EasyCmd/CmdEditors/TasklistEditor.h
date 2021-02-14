﻿#ifndef TasklistEditor_H
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

class TasklistEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit TasklistEditor(QWidget *parent = 0);
    ~TasklistEditor();

    virtual bool isModified() const;
    virtual QString getCmdName();
    virtual QString getCmdString();

private:
    Ui::TasklistEditor *ui;
    QString m_cmd;
};

#endif // TasklistEditor_H
