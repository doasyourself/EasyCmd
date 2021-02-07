#ifndef ConsoleEditor_H
#define ConsoleEditor_H

#include <QTextEdit>
#include <QTextCursor>
#include <QPointer>

class ConsoleRwWorker;
class QMenu;
class ConsoleEditor : public QTextEdit
{
    Q_OBJECT
public:
    ConsoleEditor(QWidget *parent = Q_NULLPTR);
    void appendOuput(const QString &text);

protected:
    virtual void keyPressEvent(QKeyEvent *e) override;
    virtual void keyReleaseEvent(QKeyEvent *e) override;
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;
    virtual void contextMenuEvent(QContextMenuEvent *e) override;

signals:
    /*新的输入*/
    void sigNewInput(const QString &text);

private:
    void setupActions();
    void setupMenu();

private slots:
    void slotActionCopy();
    void slotActionPaste();

private:
    /*上次输出结尾位置，上次输出结尾位置之前的内容均不可编辑*/
    int m_last_output_pos;

    /*extra selection*/
    ExtraSelection m_current_row_selection;/*当前行高亮*/
    ExtraSelection m_current_selection;/*当前选择高亮*/

    QAction *m_action_copy;/*拷贝动作*/
    QAction *m_action_paste;/*粘贴动作*/

    QMenu *m_ctx_menu;/*上下文菜单*/
};

#endif // ConsoleEditor_H
