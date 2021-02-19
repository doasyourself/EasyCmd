#include "ConsoleEditor.h"
#include "ConsoleRwWorker.h"
#include <QKeyEvent>
#include <QDebug>
#include <QMenu>
#include <QGuiApplication>
#include <QClipboard>

ConsoleEditor::ConsoleEditor(QWidget *parent)
    : QTextEdit(parent)
{
    m_current_history_index = 0;
    m_last_output_pos = this->textCursor().position();

    // 监听控制台输入命令
    connect(this, &ConsoleEditor::sigNewInput, this, &ConsoleEditor::slotNewInput);

    setFontFamily("Courier New");
    setFontPointSize(10);
    setUndoRedoEnabled(true);/*允许撤销*/
    setupActions();
    setupMenu();
}

void ConsoleEditor::appendOuput(const QString &text)
{
    // 这里不用appendText，因为append会添加新行。
    insertPlainText(text);
    m_last_output_pos = this->textCursor().position();
    moveCursor(QTextCursor::End);
}

void ConsoleEditor::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();
    Qt::KeyboardModifiers modifier = e->modifiers();

    // 限制文本漫游
    if (key == Qt::Key_Left || key == Qt::Key_PageUp || key == Qt::Key_PageDown)
    {
        QTextCursor cursor = this->textCursor();
        if (m_last_output_pos >= cursor.position())
        {
            return;
        }
        else
        {
            QTextEdit::keyPressEvent(e);
        }
    }
    else if (key == Qt::Key_Up) /*上键*/
    {
        // 开始从最新向更旧漫游
        if (m_current_history_index > 0)/*安全漫游的条件，必须*/
        {
            QTextCursor cursor = this->textCursor();
            int current_pos = cursor.position();

            // 选中当前输入的内容
            cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, current_pos - m_last_output_pos);

            // 删除当前选中的内容
            cursor.deleteChar();

            QString next_old_cmd = m_cmd_history.at(--m_current_history_index);
            cursor.insertText(next_old_cmd);

            setTextCursor(cursor);
        }
    }
    else if (key == Qt::Key_Down) /*下键*/
    {
        // 开始从最新向更旧漫游
        if (m_current_history_index < m_cmd_history.size() - 1)/*安全漫游的条件，必须*/
        {
            QTextCursor cursor = this->textCursor();
            int current_pos = cursor.position();

            // 选中当前输入的内容
            cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, current_pos - m_last_output_pos);

            // 删除当前选中的内容
            cursor.deleteChar();

            QString next_old_cmd = m_cmd_history.at(++m_current_history_index);
            cursor.insertText(next_old_cmd);

            setTextCursor(cursor);
        }
    }
    /*回退删除，删到上次输出位置就不允许删除了*/
    else if (key == Qt::Key_Backspace)
    {
        QTextCursor cursor = this->textCursor();
        if (cursor.hasSelection())
        {
            if (cursor.selectionStart() < m_last_output_pos ||
                cursor.selectionEnd() < m_last_output_pos)
            {
                return;
            }
        }
        else
        {
            if (m_last_output_pos >= cursor.position())
            {
                return;
            }
        }

        QTextEdit::keyPressEvent(e);
    }
    else if (key == Qt::Key_Return)
    {
        // 回车时，鼠标保持在当前输入的末尾，保证当前所有新的输入均为命令，
        // 而不是回车符之前的才有效
        moveCursor(QTextCursor::End);

        QTextCursor cursor = this->textCursor();
        QTextDocument *doc = document();
        int current_pos = cursor.position();

        // 获取命令字符串
        // 下面的循环条件是实验得出的
        QString cmd;
        for (int pos = m_last_output_pos; pos < current_pos; pos++)
        {
            QChar ch = doc->characterAt(pos);
            cmd.append(ch);
        }
        cmd.append("\n");

        // 回车后，清除屏幕上当前的输入，因为当前的输入会被cmd.exe输出（回显），导致命令显示两次。
        // 不是什么大问题，但这是为了和cmd.exe保持一致。
        // 下面开始选中当前输入的内容
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, current_pos - m_last_output_pos);

        // 删除当前选中的内容
        cursor.deleteChar();
        setTextCursor(cursor);

        // 发出命令通知
        emit sigNewInput(cmd);
    }
    else if (key == Qt::Key_Z && (modifier & Qt::ControlModifier)) /*给Ctrl + Z撤销加限制*/
    {
        QTextCursor cursor = this->textCursor();
        int current_pos = cursor.position();
        if (current_pos > m_last_output_pos)
        {
            QTextEdit::keyPressEvent(e);/*允许撤销*/
        }
        else
        {
            /*不允许撤销*/
        }
    }
    else if (key == Qt::Key_C && (modifier & Qt::ControlModifier)) /*解决Ctrl+C无效的问题，因为当前使用的是extraselection*/
    {
        // 用extraselection实现Ctrl+C
        slotActionCopy();
    }
    else
    {
        QTextEdit::keyPressEvent(e);
    }
}

void ConsoleEditor::keyReleaseEvent(QKeyEvent *e)
{
    QTextEdit::keyReleaseEvent(e);
}

void ConsoleEditor::mousePressEvent(QMouseEvent *e)
{
    // 左键
    Qt::MouseButton button = e->button();
    if (button & Qt::LeftButton)
    {
        int new_pos = cursorForPosition(e->pos()).position();
        if (new_pos < m_last_output_pos) /*必须加这个条件，否则会跑到新键入的内容最后*/
        {
            // 保持鼠标不动
        }
        else
        {
            QTextEdit::mousePressEvent(e);
        }

        // 实现当前行高亮
        QList<ExtraSelection> extra_sels;
        if (!isReadOnly())
        {
            QColor lineColor = QColor(Qt::gray).lighter(145);
            m_current_row_selection.format.setBackground(lineColor);
            m_current_row_selection.format.setProperty(QTextFormat::FullWidthSelection, true);
            m_current_row_selection.cursor = textCursor();
            m_current_row_selection.cursor.clearSelection();
            extra_sels.append(m_current_row_selection);

            // 保存起始选择位置
            QPalette p = this->palette();
            m_current_selection.format.setBackground(p.color(QPalette::Highlight));
            m_current_selection.format.setForeground(p.color(QPalette::HighlightedText));
            m_current_selection.cursor = textCursor();
            m_current_selection.cursor.clearSelection();
            //qDebug() << cursorForPosition(e->pos()).position();
            m_current_selection.cursor.setPosition(cursorForPosition(e->pos()).position());
        }
        setExtraSelections(extra_sels);
    }
    else if (button & Qt::LeftButton)
    {
        /**不需要右键按下自动粘贴内容，因为右键有菜单**/
    }
}

void ConsoleEditor::mouseMoveEvent(QMouseEvent *e)
{
    QList<ExtraSelection> extra_sels;
    extra_sels.append(m_current_row_selection);

    // 更新当前选择对象
    int anchor_position = m_current_selection.cursor.position();
    int current_position = cursorForPosition(e->pos()).position();
    if (current_position < anchor_position) /*左移*/
    {
        m_current_selection.cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, abs(current_position - anchor_position));
    }
    else/*右移*/
    {
        m_current_selection.cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, abs(current_position - anchor_position));
    }

    extra_sels.append(m_current_selection);
    setExtraSelections(extra_sels);
}

void ConsoleEditor::mouseReleaseEvent(QMouseEvent *e)
{
    // 上下文菜单下保持选中状态
    QList<ExtraSelection> extra_sels;
    extra_sels.append(m_current_row_selection);
    extra_sels.append(m_current_selection);
    setExtraSelections(extra_sels);
}

/*原本的双击选中会影响鼠标位置，现在统一用extraselection实现*/
void ConsoleEditor::mouseDoubleClickEvent(QMouseEvent *e)
{
    QList<ExtraSelection> extra_sels;
    extra_sels.append(m_current_row_selection);

    // 双击选择鼠标下面的单词
    m_current_selection.cursor.select(QTextCursor::WordUnderCursor);

    extra_sels.append(m_current_selection);
    setExtraSelections(extra_sels);
}

void ConsoleEditor::contextMenuEvent(QContextMenuEvent *e)
{
    m_ctx_menu->exec(mapToGlobal(e->pos()));
}

void ConsoleEditor::setupActions()
{
    m_action_copy = new QAction(tr("Copy"), this);
    m_action_paste = new QAction(tr("Paste"), this);
    connect(m_action_copy, &QAction::triggered, this, &ConsoleEditor::slotActionCopy);
    connect(m_action_paste, &QAction::triggered, this, &ConsoleEditor::slotActionPaste);
}

void ConsoleEditor::setupMenu()
{
    m_ctx_menu = new QMenu(this);
    m_ctx_menu->addAction(m_action_copy);
    m_ctx_menu->addAction(m_action_paste);
}

void ConsoleEditor::slotActionCopy()
{
    // 把当前m_current_selection的内容拷贝到剪贴板
    QString selected_text = m_current_selection.cursor.selectedText();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(selected_text);
}

void ConsoleEditor::slotActionPaste()
{
    // 把当前剪贴板内容粘贴到当前光标位置
    paste();
}

void ConsoleEditor::slotNewInput(const QString &text)
{
    m_cmd_history.append(text.trimmed()/*去除末尾的换行符*/);
    m_current_history_index = m_cmd_history.size();/*指向当前显示的内容*/
}

