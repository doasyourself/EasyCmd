#ifndef LauncherCmdEditor_H
#define LauncherCmdEditor_H

#include <QWidget>
#include <QSettings>
#include <QItemDelegate>
#include "ICmdEditor.h"
#include "LauncherCommand.h"

namespace Ui {
class LauncherCmdEditor;
}

class QTableWidgetItem;
/********************************************************************/
class LauncherCmdEditor : public ICmdEditor
{
    Q_OBJECT

public:
    // 列定义
    enum ColDefine
    {
        COL_NAME = 0,
        COL_PATH
    };

    // 入口
    struct Entry
    {
        QString name;
        QString path;
    };

public:
    explicit LauncherCmdEditor(LauncherCommand *command, QWidget *parent = nullptr);
    ~LauncherCmdEditor();

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);

protected:
    QString getCmdString();

    // 加载入口
    void loadEntries();

    // 保存入口
    void saveEntries();

private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_del_clicked();
    void slotItemClicked(QTableWidgetItem *item);
    void slotItemChanged(QTableWidgetItem *item);
    void slotCurrentRowChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    Ui::LauncherCmdEditor *ui;
    LauncherCommand *m_command;

    QSettings m_settings;
    QString m_cmd;
};

#endif // LauncherCmdEditor_H
