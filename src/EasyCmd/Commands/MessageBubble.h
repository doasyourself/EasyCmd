#ifndef MESSAGEBUBBLE_H
#define MESSAGEBUBBLE_H

#include <QWidget>

namespace Ui {
class MessageBubble;
}

class MessageBubble : public QWidget
{
    Q_OBJECT

public:
    explicit MessageBubble(QWidget *parent = 0);
    ~MessageBubble();

private:
    Ui::MessageBubble *ui;
};

#endif // MESSAGEBUBBLE_H
