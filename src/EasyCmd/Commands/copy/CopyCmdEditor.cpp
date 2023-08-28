#include "CopyCmdEditor.h"
#include "ui_CopyCmdEditor.h"
#include <QFileDialog>
#include <QMessageBox>

CopyCmdEditor::CopyCmdEditor(CopyCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::CopyCmdEditor),
    m_command(command)
{
    ui->setupUi(this);

    check();
}

CopyCmdEditor::~CopyCmdEditor()
{
    delete ui;
}

bool CopyCmdEditor::isModified() const
{
    return true;
}

QString CopyCmdEditor::getCmdString()
{
    // 源路径
    QString srcFilepath;

    QStringList quoted_filelist;
    foreach (const QString &selectFile, m_selectedSrcFiles)
    {
        // 加引号
        quoted_filelist.append(QString("\"%1\"").arg(selectFile));
    }

    srcFilepath = quoted_filelist.join("+");

    // 目标路径
    QString destFilepath = ui->lineEdit_destFilepath->text();

    // 选项
    QString options = getOptions();

    // 生成命令
    QString cmd;
    if (options.isEmpty())
    {
        cmd = QString("%1 \"%2\" \"%3\"").arg(m_command->getCmdName(),
            srcFilepath, destFilepath);
    }
    else
    {
        cmd = QString("%1 %2 \"%3\" \"%4\"").arg(m_command->getCmdName(),
            options, srcFilepath, destFilepath);
    }

    return cmd;
}

QString CopyCmdEditor::getOptions()
{
    QString options;
    QStringList optionList;

    if (ui->chbox_option_d->isChecked())
    {
        optionList << "/d";
    }

    if (ui->chbox_option_v->isChecked())
    {
        optionList << "/v";
    }

    if (ui->chbox_option_n->isChecked())
    {
        optionList << "/n";
    }

    if (ui->chbox_option_y->isChecked())
    {
        optionList << "/y";
    }

    if (ui->chbox_option_not_y->isChecked())
    {
        optionList << "/-y";
    }

    if (ui->chbox_option_z->isChecked())
    {
        optionList << "/z";
    }

    if (ui->chbox_option_a->isChecked())
    {
        optionList << "/a";
    }

    if (ui->chbox_option_b->isChecked())
    {
        optionList << "/b";
    }

    if (ui->chBox_option_help->isChecked())
    {
        optionList << "/?";
    }

    options = optionList.join(" ");
    return options;
}

bool CopyCmdEditor::check()
{
    bool ok = true;

    if (ui->edit_srcFilepath->toPlainText().isEmpty())
    {
        ok = false;
        ui->label_srcFilepath_warning->setText("源文件路径不能为空！");
        ui->label_srcFilepath_warning->setVisible(true);
    }
    else
    {
        ui->label_srcFilepath_warning->setVisible(false);
    }

    if (ui->label_destFilepath_warning->text().isEmpty())
    {
        ok = false;
        ui->label_destFilepath_warning->setText("目标文件路径不能为空！");
        ui->label_destFilepath_warning->setVisible(true);
    }
    else
    {
        ui->label_destFilepath_warning->setVisible(false);
    }

    return ok;
}

void CopyCmdEditor::on_chBox_option_help_toggled(bool checked)
{
    check();
    emit sigModified();
}


void CopyCmdEditor::on_btn_browserSourceFilepath_clicked()
{
    // 当前路径信息
    QFileInfo fi(ui->edit_srcFilepath->toPlainText());

    // 在当前路径下选择目录
    m_selectedSrcFiles = QFileDialog::getOpenFileNames(
        this, tr("Choose src filepath"), fi.path());

    // 更新路径显示
    if (!m_selectedSrcFiles.isEmpty())
    {
        // 一定要转成本地分隔符，否则命令行不识别
        foreach (const QString &selectFile, m_selectedSrcFiles)
        {
            ui->edit_srcFilepath->append(QDir().toNativeSeparators(selectFile));
        }

        ui->label_srcFilepath_warning->hide();
    }

    // 通知命令改变
    emit sigModified();
}

void CopyCmdEditor::on_btn_browserDestFilepath_clicked()
{
    // 用户选择的目录路径
    QString selected_path;
    QFileInfo fi;

    // 当前路径信息
    int srcFileCount = m_selectedSrcFiles.size();
    if (srcFileCount > 0)
    {
        QString default_destFilepath = m_selectedSrcFiles.first();
        if (!default_destFilepath.isEmpty())
        {
            fi.setFile(default_destFilepath);
        }
    }

    // 在当前路径下选择目录
    selected_path = QFileDialog::getSaveFileName(
        this, tr("Choose dest filepath"),
        srcFileCount == 1 ? fi.absoluteFilePath() : fi.absolutePath()
    );

    // 更新路径显示
    if (!selected_path.isEmpty())
    {
        QFileInfo fi2(selected_path);
        if (fi2.isFile())
        {
            QMessageBox::information(this, "提示", "源参数为多个文件时，目标参数只能是路径");
        }

        selected_path = fi.absolutePath();

        // 一定要转成本地分隔符，否则命令行不识别
        ui->lineEdit_destFilepath->setText(QDir().toNativeSeparators(selected_path));
        ui->label_destFilepath_warning->hide();
    }

    // 通知命令改变
    emit sigModified();
}


void CopyCmdEditor::on_chbox_option_d_toggled(bool checked)
{
    check();
    emit sigModified();
}


void CopyCmdEditor::on_chbox_option_v_toggled(bool checked)
{
    check();
    emit sigModified();
}

void CopyCmdEditor::on_chbox_option_n_toggled(bool checked)
{
    check();
    emit sigModified();
}

void CopyCmdEditor::on_chbox_option_not_y_toggled(bool checked)
{
    check();
    emit sigModified();

    if (checked)
    {
        ui->chbox_option_y->setChecked(false);
    }
}

void CopyCmdEditor::on_chbox_option_z_toggled(bool checked)
{
    check();
    emit sigModified();
}

void CopyCmdEditor::on_chbox_option_a_toggled(bool checked)
{
    check();
    emit sigModified();
}

void CopyCmdEditor::on_chbox_option_b_toggled(bool checked)
{
    check();
    emit sigModified();
}

void CopyCmdEditor::on_chbox_option_y_toggled(bool checked)
{
    check();
    emit sigModified();

    if (checked)
    {
        ui->chbox_option_not_y->setChecked(false);
    }
}

void CopyCmdEditor::on_edit_srcFilepath_textChanged()
{
    check();
    emit sigModified();

    // 更新文件列表
    m_selectedSrcFiles = ui->edit_srcFilepath->toPlainText().split("\n");
}

void CopyCmdEditor::on_btn_addSrcDirpath_clicked()
{
    // 在当前路径下选择目录
    QString selectedDir = QFileDialog::getExistingDirectory(
        this, tr("Choose src filepath"));
    selectedDir = QDir::toNativeSeparators(selectedDir);
    m_selectedSrcFiles.append(selectedDir);

    // 添加到列表
    ui->edit_srcFilepath->append(QString("%1").arg(selectedDir));
}

