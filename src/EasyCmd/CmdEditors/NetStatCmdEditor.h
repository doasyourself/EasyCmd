#ifndef NetStatCmdEditor_H
#define NetStatCmdEditor_H

#include <QWidget>
#include "ICmdEditor.h"

namespace Ui {
class NetStatCmdEditor;
}

class NetStatCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit NetStatCmdEditor(QWidget *parent = 0);
    virtual ~NetStatCmdEditor();

    virtual bool isModified() const;
    virtual QString getCmdName();
    virtual QString getCmdString();

private slots:
    void on_checkBox_option_s_toggled(bool checked);

    void on_checkBox_option_p_toggled(bool checked);

    void on_checkBox_option_interval_toggled(bool checked);

private:
    Ui::NetStatCmdEditor *ui;
};

#endif // NetStatCmdEditor_H
