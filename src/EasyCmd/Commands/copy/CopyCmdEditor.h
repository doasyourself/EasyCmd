#ifndef COPYCMDEDITOR_H
#define COPYCMDEDITOR_H

#include <QWidget>
#include "ICmdEditor.h"
#include "CopyCommand.h"

namespace Ui {
class CopyCmdEditor;
}

class CopyCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    explicit CopyCmdEditor(CopyCommand *command, QWidget *parent = 0);
    ~CopyCmdEditor();

    virtual bool isModified() const;

    virtual QString getCmdString();

protected:
    QString getOptions();
    bool check();

private slots:
    void on_chBox_option_help_toggled(bool checked);

    void on_btn_browserSourceFilepath_clicked();

    void on_btn_browserDestFilepath_clicked();

    void on_chbox_option_d_toggled(bool checked);

    void on_chbox_option_v_toggled(bool checked);

    void on_chbox_option_n_toggled(bool checked);

    void on_chbox_option_y_toggled(bool checked);

    void on_chbox_option_not_y_toggled(bool checked);

    void on_chbox_option_z_toggled(bool checked);

    void on_chbox_option_a_toggled(bool checked);

    void on_chbox_option_b_toggled(bool checked);

    void on_edit_srcFilepath_textChanged();

    void on_btn_addSrcDirpath_clicked();

private:
    Ui::CopyCmdEditor *ui;
    CopyCommand *m_command;

    QStringList m_selectedSrcFiles; // 选择的文件列表
};

#endif // COPYCMDEDITOR_H
