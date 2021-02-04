#include "EditorFactory.h"
#include "PingCmdEditor.h"
#include "NetStatCmdEditor.h"
#include "SystemToolEditor.h"

QWidget *newPingCmdEditor() { return new PingCmdEditor; }
QWidget *newNetStatCmdEditor() { return new NetStatCmdEditor; }
QWidget *newSystemToolsEditor() { return new SystemToolEditor; }

EditorFactory::EditorFactory()
{
    m_editor_map.clear();

    // 关键字小写
    m_editor_map.insert("ping", newPingCmdEditor);
    m_editor_map.insert("netstat", newNetStatCmdEditor);
    m_editor_map.insert("systemTools", newSystemToolsEditor);
}

QWidget *EditorFactory::createEditor(const QString &name)
{
    QWidget *editor = NULL;
    newEditorFunc func = m_editor_map.value(name);
    if (func) editor = func();
    return editor;
}
