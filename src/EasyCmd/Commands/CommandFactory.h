#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

/*******************************************************************************
** 此类为命令行编辑器工厂类
**
*******************************************************************************/

#include <QString>
#include <QWidget>
#include <QMap>
#include <QPluginLoader>

#include "IUnifiedBase.h"

class CommandFactory
{
public:
    CommandFactory();
    ~CommandFactory();

    // 创建命令对象
    IUnifiedBase *createCommand(const QString &command_id);

private:
    // 使用hash加速创建
    QHash<QString, QPluginLoader *> m_command_plugin_map;
};

#endif // CMDEDITORFACTORY_H
