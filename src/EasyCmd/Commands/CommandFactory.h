#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

/*******************************************************************************
** 此类为命令行编辑器工厂类
**
*******************************************************************************/

#include <QString>
#include <QWidget>
#include <QMap>

#include "IUnifiedBase.h"

class CommandFactory
{
public:
    CommandFactory();

    // 创建命令对象
    IUnifiedBase *createCommand(const QString &command_id);

private:
    typedef IUnifiedBase *(*newEditorFunc)();

    // 使用hash加速创建
    QHash<QString, newEditorFunc> m_editor_map;
};

#endif // CMDEDITORFACTORY_H
