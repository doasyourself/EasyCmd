#ifndef NetStatCmdEditor_H
#define NetStatCmdEditor_H

#include <QWidget>
#include "ICmdEditor.h"
#include "NetStatCommand.h"

namespace Ui {
class NetStatCmdEditor;
}

class NetStatCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit NetStatCmdEditor(NetStatCommand *command, QWidget *parent = 0);
    virtual ~NetStatCmdEditor();

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);

protected:
    QString getCmdString();

private slots:
    void on_checkBox_option_s_toggled(bool checked);

    void on_checkBox_option_p_toggled(bool checked);

    void on_checkBox_option_interval_toggled(bool checked);

    void slot_checkBox_clicked();

private:
    Ui::NetStatCmdEditor *ui;
    NetStatCommand *m_command;
};

#endif // NetStatCmdEditor_H
