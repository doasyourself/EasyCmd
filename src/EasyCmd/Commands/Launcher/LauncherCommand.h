#ifndef LAUNCHERCOMMAND_H
#define LAUNCHERCOMMAND_H

#include <QObject>
#include "ICommand.h"

class LauncherCommand : public QObject, public ICommand
{
    Q_OBJECT
public:
    explicit LauncherCommand(QObject *parent = nullptr);

    /**
     * @brief getCmdName
     *  获取命令名称，在编辑器初始化后作为初始命令显示。
     * @return
     */
    virtual QString getCmdName();

    /**
     * @brief getEditorWidget
     *  获取命令编辑器
     * @return
     */
    virtual ICmdEditor *createCmdEditorWidget();
};

#endif // LAUNCHERCOMMAND_H
