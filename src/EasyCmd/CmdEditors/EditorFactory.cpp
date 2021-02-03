#include "EditorFactory.h"
#include "PingCmdEditor.h"
#include "NetStatCmdEditor.h"

QWidget *newPingCmdEditor() { return new PingCmdEditor; }
QWidget *newNetStatCmdEditor() { return new NetStatCmdEditor; }

EditorFactory::EditorFactory()
{
    m_editor_map.clear();

    // 关键字小写
    m_editor_map.insert("ping", newPingCmdEditor);
    m_editor_map.insert("netstat", newNetStatCmdEditor);
}

QWidget *EditorFactory::createEditor(const QString &name)
{
    QWidget *editor = NULL;
    newEditorFunc func = m_editor_map.value(name);
    editor = func();
    return editor;
}
