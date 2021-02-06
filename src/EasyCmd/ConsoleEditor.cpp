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
    //moveCursor(QTextCursor::End);
    m_last_output_pos = this->textCursor().position();
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
    QTextEdit::mousePressEvent(e);
    moveCursor(QTextCursor::End);
}
