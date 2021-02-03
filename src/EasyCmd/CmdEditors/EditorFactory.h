#ifndef EDITORFACTORY_H
#define EDITORFACTORY_H

#include <QString>
#include <QWidget>
#include <QMap>

class EditorFactory
{
public:
    EditorFactory();

    QWidget *createEditor(const QString &editor_name);

private:
    typedef QWidget *(*newEditorFunc)(); /*代替工厂模式，少些点代码*/
    QMap<QString, newEditorFunc> m_editor_map;
};

#endif // EDITORFACTORY_H
