#ifndef EDITORFACTORY_H
#define EDITORFACTORY_H

#include <QString>
#include <QWidget>
#include <QMap>

class ICmdEditor;
class EditorFactory
{
public:
    EditorFactory();

    ICmdEditor *createEditor(const QString &editor_name);

private:
    typedef ICmdEditor *(*newEditorFunc)(); /*代替工厂模式，少些点代码*/
    QMap<QString, newEditorFunc> m_editor_map;
};

#endif // EDITORFACTORY_H
