#include "LauncherCmdEditor.h"
#include "ui_LauncherCmdEditor.h"
#include <QStyle>
#include <QFileInfo>

/*******************************************************************/
LauncherCmdEditor::LauncherCmdEditor(LauncherCommand *command, QWidget *parent) :
    ICmdEditor(parent),
    ui(new Ui::LauncherCmdEditor),
    m_command(command),
    m_settings("./LauncherEntries.ini", QSettings::IniFormat)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnWidth(COL_NAME, 200);
    ui->tableWidget->setColumnWidth(COL_PATH, 400);

    // 加载入口
    loadEntries();

    // 监听表格信号
    connect(ui->tableWidget, &QTableWidget::itemClicked,
            this, &LauncherCmdEditor::slotItemClicked);
    connect(ui->tableWidget, &QTableWidget::itemChanged,
            this, &LauncherCmdEditor::slotItemChanged);
    connect(ui->tableWidget->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &LauncherCmdEditor::slotCurrentRowChanged);
}

LauncherCmdEditor::~LauncherCmdEditor()
{
    saveEntries();
    delete ui;
}

int LauncherCmdEditor::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;

    switch (propertyId)
    {
    case PID_CMDSTRING:
    {
        out_property = getCmdString();
        break;
    }
    default:
    {
        break;
    }
    }

    return code;
}

int LauncherCmdEditor::setProperty(int propertyId, const QVariant &property)
{
    return 0;
}

void LauncherCmdEditor::loadEntries()
{
    // 读取配置
    QList<Entry> entries;
    int size = m_settings.beginReadArray("Entry");
    for (int i = 0; i < size; i++)
    {
        m_settings.setArrayIndex(i);
        Entry entry;
        entry.name = m_settings.value("name").toString();
        entry.path = m_settings.value("path").toString();
        entries.append(entry);
    }
    m_settings.endArray();

    // 载入到表格
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(size);
    for (int i = 0; i < size; i++)
    {
        const Entry &entry = entries.at(i);
        QTableWidgetItem *item = ui->tableWidget->item(i, COL_NAME);
        if (!item)
        {
            item = new QTableWidgetItem;
            ui->tableWidget->setItem(i, COL_NAME, item);
        }
        item->setText(entry.name);

        item = ui->tableWidget->item(i, COL_PATH);
        if (!item)
        {
            item = new QTableWidgetItem;
            ui->tableWidget->setItem(i, COL_PATH, item);
        }
        item->setText(entry.path);
    }
}

void LauncherCmdEditor::saveEntries()
{
    m_settings.clear();

    QList<Entry> entries;
    int row_count = ui->tableWidget->rowCount();
    for (int i = 0; i < row_count; i++)
    {
        Entry entry;
        QTableWidgetItem *item = ui->tableWidget->item(i, COL_NAME);
        if (item)
        {
            entry.name = item->text();
        }

        item = ui->tableWidget->item(i, COL_PATH);
        if (item)
        {
            entry.path = item->text();
        }

        entries.append(entry);
    }

    m_settings.beginWriteArray("Entry");
    int size = entries.size();
    for (int i = 0; i < size; i++)
    {
        const Entry &e = entries.at(i);
        m_settings.setArrayIndex(i);
        m_settings.setValue("name", e.name);
        m_settings.setValue("path", e.path);
    }
    m_settings.endArray();

    // 同步到文件
    m_settings.sync();
}

QString LauncherCmdEditor::getCmdString()
{
    return m_cmd;
}

void LauncherCmdEditor::on_pushButton_add_clicked()
{
    int row_count = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row_count + 1);

    int row_index = row_count;

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText("New Item");
    ui->tableWidget->setItem(row_index, COL_NAME, item);

    item = new QTableWidgetItem;
    ui->tableWidget->setItem(row_index, COL_PATH, item);
}

void LauncherCmdEditor::on_pushButton_del_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    saveEntries();
}

void LauncherCmdEditor::slotItemClicked(QTableWidgetItem *item)
{
    QString new_cmd;
    int row = item->row();
    QTableWidgetItem *path_item = ui->tableWidget->item(row, COL_PATH);
    if (path_item)
    {
        QString filepath = path_item->text();
        QFileInfo fi(filepath);

        // 如果是符号链接则将filepath指向源文件
        if (fi.isSymLink())
        {
            filepath = fi.symLinkTarget();
        }

        new_cmd = QString("\"%1\"\n").arg(filepath);/*路径可能包含空格，要用引号包起来*/

        // 判断命令是否改变
        if (new_cmd != m_cmd)
        {
            m_cmd = new_cmd;
            emit sigNotify(SID_MODIFIED, QVariantHash());
        }
    }
}

void LauncherCmdEditor::slotItemChanged(QTableWidgetItem *item)
{
    saveEntries();
}

void LauncherCmdEditor::slotCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    // 自动清空
    if (!current.isValid())
    {
        m_cmd.clear();
        emit sigNotify(SID_MODIFIED, QVariantHash());
    }
}
