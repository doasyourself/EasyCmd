#ifndef IPCONFIGEDITOR_H
#define IPCONFIGEDITOR_H

#include <QWidget>
#include "ICmdEditor.h"

namespace Ui {
class IpconfigEditor;
}

class IpconfigEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit IpconfigEditor(QWidget *parent = 0);
    ~IpconfigEditor();

    virtual bool isModified() const;
    virtual QString getCmdString();


private slots:
    void on_checkBox_setclassid_toggled(bool checked);

    void on_checkBox_showclassid_toggled(bool checked);

    void on_checkBox_release_toggled(bool checked);

    void on_checkBox_renew_toggled(bool checked);

    void on_checkBox_all_toggled(bool checked);

    void on_checkBox_flushdns_toggled(bool checked);

    void on_checkBox_displaydns_toggled(bool checked);

    void slotOptionChanged();

private:
    void genCmdString();

private:
    Ui::IpconfigEditor *ui;
    QString m_cmd;
};

#endif // IPCONFIGEDITOR_H
