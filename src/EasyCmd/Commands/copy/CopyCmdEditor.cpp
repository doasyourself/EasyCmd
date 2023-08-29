#include "CopyCmdEditor.h"
#include "ui_CopyCmdEditor.h"
#include <QFileDialog>
#include <QMessageBox>

CopyCmdEditor::CopyCmdEditor(CopyCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::CopyCmdEditor),
    m_command(command),
    m_button_group(new QButtonGroup(this))
{
    ui->setupUi(this);

    m_button_group->addButton(ui->radioBtn_singleFile);
    m_button_group->addButton(ui->radioBtn_singleDir);
    m_button_group->addButton(ui->radioBtn_srcFiles);

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
    QString cmd;

    // 源路径
    QString srcFilepath = "\"\"";
    if (ui->radioBtn_singleFile->isChecked())
    {
        srcFilepath = QString("\"%1\"").arg(ui->lineEdit_singleFilepath->text());
    }
    else if (ui->radioBtn_singleDir->isChecked())
    {
        srcFilepath = QString("\"%1\"").arg(ui->lineEdit_srcDirpath->text());
    }
    else if (ui->radioBtn_srcFiles->isChecked())
    {
        QStringList quoted_filelist;
        foreach (const QString &selectFile, m_selectedSrcFiles)
        {
            // 加引号
            quoted_filelist.append(QString("\"%1\"").arg(selectFile));
        }

        if (!quoted_filelist.isEmpty())
        {
            srcFilepath = quoted_filelist.join("+");
        }
    }

    if (srcFilepath.isEmpty())
    {
        ui->label_srcFilepath_warning->setText("源路径不能为空！");
    }

    // 目标路径
    QString destFilepath = ui->lineEdit_destFilepath->text();

    // 选项
    QString options = getOptions();

    // 生成命令
    if (options.isEmpty())
    {
        cmd = QString("%1 %2 \"%3\"").arg(m_command->getCmdName(),
            srcFilepath, destFilepath);
    }
    else
    {
        cmd = QString("%1 %2 %3 \"%4\"").arg(m_command->getCmdName(),
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

    if (ui->chbox_option_a->isChecked() ||
       (ui->radioBtn_srcFiles->isChecked() && ui->radioBtn_text_merge->isChecked()))
    {
        optionList << "/a";
    }

    if (ui->chbox_option_b->isChecked() ||
       (ui->radioBtn_srcFiles->isChecked() && ui->radioBtn_bin_merge->isChecked()))
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
    bool ok1 = true;

    // 源路径
    if (ui->lineEdit_singleFilepath->text().isEmpty() &&
        ui->lineEdit_srcDirpath->text().isEmpty() &&
        ui->plainTextEdit_srcFilepathList->toPlainText().isEmpty())
    {
        ok1 = false;
        ui->label_srcFilepath_warning->setText("源文件路径不能为空！");
    }

    ui->label_srcFilepath_warning->setVisible(!ok1);

    bool ok2 = true;
    do
    {
        // 目标路径
        if (ui->lineEdit_destFilepath->text().isEmpty())
        {
            ok2 = false;
            ui->label_destFilepath_warning->setText("目标路径不能为空！");
            break;
        }

        // 检查目标路径类型
        if (ui->radioBtn_singleDir->isChecked())
        {
            // 源文件是文件夹，目的文件只能是文件夹
            QFileInfo fi(ui->lineEdit_destFilepath->text());
            if (!fi.isDir())
            {
                ok2 = false;
                ui->label_destFilepath_warning->setText("源路径是文件夹，目的只能是文件夹");
                break;
            }
        }
        else if (ui->radioBtn_srcFiles->isChecked())
        {
            // 源文件是多个文件，目的文件只能是文件
            QFileInfo fi(ui->lineEdit_destFilepath->text());
            if (!fi.isFile())
            {
                ok2 = false;
                ui->label_destFilepath_warning->setText("源路径是多个文件，目的路径只能是文件");
                break;
            }
        }

    } while (0);

    ui->label_destFilepath_warning->setVisible(!ok2);

    return ok1 && ok2;
}

void CopyCmdEditor::on_chBox_option_help_toggled(bool checked)
{
    check();
    emit sigModified();
}


void CopyCmdEditor::on_btn_browserSourceFilepath_clicked()
{
    // 当前路径信息
    QFileInfo fi(ui->lineEdit_singleFilepath->text());

    QString selectedFile = QFileDialog::getOpenFileName(
        this, tr("Choose src file"), fi.path());

    // 更新路径显示
    if (!selectedFile.isEmpty())
    {
        ui->lineEdit_singleFilepath->setText(selectedFile);
        ui->label_srcFilepath_warning->hide();
    }

    // 通知命令改变
    emit sigModified();
}

void CopyCmdEditor::on_btn_browserDestFilepath_clicked()
{
    // 用户选择的目录路径
    QString selectedPath;
    QFileInfo fi;

    if (ui->radioBtn_singleFile->isChecked())
    {
        fi.setFile(ui->lineEdit_singleFilepath->text());

        if (ui->radio_destIsFile->isChecked())
        {
            selectedPath = QFileDialog::getSaveFileName(
                this, tr("Choose dest filepath"), fi.absoluteFilePath()
            );
        }
        else if (ui->radio_destIsDir->isChecked())
        {
            selectedPath = QFileDialog::getExistingDirectory(
                this, tr("Choose dest dir"), fi.absoluteFilePath()
            );
        }
    }
    else if (ui->radioBtn_srcFiles->isChecked())
    {
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

        selectedPath = QFileDialog::getSaveFileName(
            this, tr("Choose dest filepath"), fi.absoluteFilePath()
        );
    }
    else if (ui->radioBtn_singleDir->isChecked())
    {
        selectedPath = QFileDialog::getExistingDirectory(
            this, tr("Choose dest path"), fi.absolutePath()
        );
    }
    else
    {
        Q_ASSERT(0);
    }

    // 更新路径显示
    if (!selectedPath.isEmpty())
    {
        // 一定要转成本地分隔符，否则命令行不识别
        ui->lineEdit_destFilepath->setText(QDir().toNativeSeparators(selectedPath));
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

void CopyCmdEditor::on_lineEdit_destFilepath_textChanged(const QString &arg1)
{
    check();
    emit sigModified();
}

void CopyCmdEditor::on_btn_browserSrcDir_clicked()
{
    QString tmp = ui->lineEdit_srcDirpath->text();
    QString selectedDir = QFileDialog::getExistingDirectory(
        this, tr("Choose dest filepath"), QFileInfo(tmp).absolutePath()
    );

    ui->lineEdit_srcDirpath->setText(QDir::toNativeSeparators(selectedDir));
}

void CopyCmdEditor::on_plainTextEdit_srcFilepathList_textChanged()
{
    check();

    // 更新文件列表
    m_selectedSrcFiles = ui->plainTextEdit_srcFilepathList->toPlainText().split("\n");
    emit sigModified();
}


void CopyCmdEditor::on_btn_addSrcFilepath_clicked()
{
    QString tmp = ui->plainTextEdit_srcFilepathList->toPlainText();
    QStringList selectedFiles = QFileDialog::getOpenFileNames(
        this, tr("Choose dest filepath"), QFileInfo(tmp).absolutePath()
    );

    foreach (QString file, selectedFiles)
    {
        if (!m_selectedSrcFiles.contains(file))
        {
            // 转为本地斜杠
            file = QDir::toNativeSeparators(file);

            m_selectedSrcFiles.append(file);
            ui->plainTextEdit_srcFilepathList->appendPlainText(file);
        }
    }
}

void CopyCmdEditor::on_radioBtn_singleFile_toggled(bool checked)
{
    ui->widget_singleSrcFile->setEnabled(checked);

    if (checked)
    {
        ui->widget_destType->setEnabled(true);
    }

    check();
    emit sigModified();
}

void CopyCmdEditor::on_radioBtn_singleDir_toggled(bool checked)
{
    ui->widget_srcDir->setEnabled(checked);

    if (checked)
    {
        // 目标只能是文件夹
        ui->radio_destIsDir->setChecked(true);
        ui->widget_destType->setEnabled(false);
    }

    check();
    emit sigModified();
}

void CopyCmdEditor::on_radioBtn_srcFiles_toggled(bool checked)
{
    ui->widget_srcFiles->setEnabled(checked);

    if (checked)
    {
        // 目标只能是文件
        ui->radio_destIsFile->setChecked(true);
        ui->widget_destType->setEnabled(false);
    }

    check();
    emit sigModified();
}

void CopyCmdEditor::on_radioBtn_bin_merge_toggled(bool checked)
{
    check();
    emit sigModified();
}


void CopyCmdEditor::on_radioBtn_text_merge_toggled(bool checked)
{
    check();
    emit sigModified();
}

