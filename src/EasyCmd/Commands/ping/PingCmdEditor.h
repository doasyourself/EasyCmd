#ifndef PINGCMDEDITOR_H
#define PINGCMDEDITOR_H

#include <QWidget>
#include "ICmdEditor.h"
#include "PingCommand.h"

namespace Ui {
class PingCmdEditor;
}

class PingCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit PingCmdEditor(PingCommand *command, QWidget *parent = 0);
    virtual ~PingCmdEditor();

    virtual bool isModified() const;
    virtual QString getCmdString();

private slots:
    void on_checkBox_option_l_toggled(bool checked);

    void on_checkBox_option_i_toggled(bool checked);

    void on_checkBox_option_w_toggled(bool checked);

    void on_lineEdit_ip_url_textChanged(const QString &arg1);

    void on_checkBox_infiniteTimes_toggled(bool checked);

    void on_checkBox_finiteTimes_toggled(bool checked);

private:
    Ui::PingCmdEditor *ui;
    PingCommand *m_command;
};

#endif // PINGCMDEDITOR_H
