#include "CommandFactory.h"

#include <QPluginLoader>
#include <QDir>
#include <QApplication>
#include <QFileInfo>
#include <QDebug>

CommandFactory::CommandFactory()
{
    // 关键字小写
    // 注册/保存所有创建接口
    QDir pluginDir(QApplication::applicationDirPath() + QDir::separator() + "commands");
    QFileInfoList fileInfos = pluginDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    // 加载插件
    foreach (const QFileInfo &fileInfo, fileInfos)
    {
        if (fileInfo.isDir())
        {
            // 添加库目录
            qApp->addLibraryPath(fileInfo.absolutePath());

            // 加载插件
            QString cmd_name = fileInfo.baseName();
            QString plugin_path = QDir(fileInfo.absoluteFilePath()).absoluteFilePath(cmd_name+".dll");

            QPluginLoader *plugin_loader = new QPluginLoader(plugin_path);
            m_command_plugin_map.insert(cmd_name, plugin_loader);
        }
    }
}

CommandFactory::~CommandFactory()
{
    qDeleteAll(m_command_plugin_map);
    m_command_plugin_map.clear();
}

IUnifiedBase *CommandFactory::createCommand(const QString &command_id)
{
    IUnifiedBase *command = NULL;
    QPluginLoader *loader = m_command_plugin_map.value(command_id);
    if (loader)
    {
        command = qobject_cast<IUnifiedBase *>(loader->instance());
    }

    return command;
}
