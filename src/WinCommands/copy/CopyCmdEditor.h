#ifndef COPYCMDEDITOR_H
#define COPYCMDEDITOR_H

#include <QWidget>
#include <QButtonGroup>

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

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);

protected:
    QString getOptions();
    bool check();
    QString getCmdString();

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

    void on_lineEdit_destFilepath_textChanged(const QString &arg1);

    void on_btn_browserSrcDir_clicked();

    void on_plainTextEdit_srcFilepathList_textChanged();

    void on_btn_addSrcFilepath_clicked();

    void on_radioBtn_singleFile_toggled(bool checked);

    void on_radioBtn_singleDir_toggled(bool checked);

    void on_radioBtn_srcFiles_toggled(bool checked);

    void on_radioBtn_bin_merge_toggled(bool checked);

    void on_radioBtn_text_merge_toggled(bool checked);

private:
    Ui::CopyCmdEditor *ui;
    CopyCommand *m_command;

    QStringList m_selectedSrcFiles; // 选择的文件列表
    QButtonGroup *m_button_group; // 按钮组
};

#endif // COPYCMDEDITOR_H
