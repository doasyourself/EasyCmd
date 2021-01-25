#ifndef PINGCMDEDITOR_H
#define PINGCMDEDITOR_H

#include <QWidget>
#include "ICmdEditor.h"

namespace Ui {
class PingCmdEditor;
}

class PingCmdEditor : public QWidget, public ICmdEditor
{
    Q_OBJECT

public:
    explicit PingCmdEditor(QWidget *parent = 0);
    virtual ~PingCmdEditor();

    virtual bool isModified() const;
    virtual QString getCmdString();

private:
    Ui::PingCmdEditor *ui;
};

#endif // PINGCMDEDITOR_H
