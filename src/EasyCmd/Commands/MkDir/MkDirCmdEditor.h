#ifndef MkDirCmdEditor_H
#define MkDirCmdEditor_H

#include <QWidget>
#include "ICmdEditor.h"
#include "MkDirCommand.h"

namespace Ui {
class MkDirCmdEditor;
}

class MkDirCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit MkDirCmdEditor(MkDirCommand *command, QWidget *parent = 0);
    ~MkDirCmdEditor();

    virtual bool isModified() const;

    virtual QString getCmdString();

private slots:
    void on_lineEdit_arg_dirpath_textChanged(const QString &dirpath);

    void on_checkBox_option_d_toggled(bool checked);

private:
    Ui::MkDirCmdEditor *ui;
    MkDirCommand *m_command;
};

#endif // MkDirCmdEditor_H
