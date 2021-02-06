#include "ConsoleEditor.h"
#include "ConsoleRwWorker.h"
#include <QKeyEvent>
#include <QDebug>

ConsoleEditor::ConsoleEditor(QWidget *parent)
    : QTextEdit(parent)
{
    m_last_output_pos = this->textCursor().position();
}

void ConsoleEditor::appendOuput(const QString &text)
{
    this->append(text);
    m_last_output_pos = this->textCursor().position();

    QList<ExtraSelection> extra_selection;
    ExtraSelection sel;
    sel.cursor.setPosition(2, QTextCursor::MoveAnchor);//移到起始位置
    sel.cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor, 30);//移动结束位置
    //sel.cursor.select(QTextCursor::WordUnderCursor);//选择
    sel.format = this->currentCharFormat();
    extra_selection.append(sel);
    setExtraSelections(extra_selection);
}

void ConsoleEditor::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();

    // 限制向左选择
    if (key == Qt::Key_Left)
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
        QTextEdit::keyPressEvent(e);

        QTextDocument *doc = document();
        int current_pos = this->textCursor().position();

        QString cmd;

        // 下面的循环条件是实验得出的
        for (int pos = m_last_output_pos; pos < current_pos - 1; pos++)
        {
            QChar ch = doc->characterAt(pos);
            cmd.append(ch);
        }
        cmd.append("\n");

        // 发出通知
        emit sigNewInput(cmd);
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
            // 鼠标始终保持在上次输出的末尾
            moveCursor(QTextCursor::End);
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
}
