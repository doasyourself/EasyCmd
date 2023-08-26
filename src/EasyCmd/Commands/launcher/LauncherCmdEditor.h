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

    // 加载入口
    void loadEntries();

    // 保存入口
    void saveEntries();

    virtual bool isModified() const;
    virtual QString getCmdName();
    virtual QString getCmdString();

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
