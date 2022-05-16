#ifndef CMDEDITORFACTORY_H
#define CMDEDITORFACTORY_H

/*******************************************************************************
** 此类为命令行编辑器工厂类
**
*******************************************************************************/

#include <QString>
#include <QWidget>
#include <QMap>

class ICmdEditor;
class CmdEditorFactory
{
public:
    CmdEditorFactory();

    // 创建命令行编辑器
    ICmdEditor *createEditor(const QString &editor_name);

private:
    typedef ICmdEditor *(*newEditorFunc)();

    // 用于优化工厂模式，可以避免过多的if else来判断对象类型，使用QMap速度更快
    QMap<QString, newEditorFunc> m_editor_map;
};

#endif // CMDEDITORFACTORY_H
