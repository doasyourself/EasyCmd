#include "MessageBubble.h"
#include "ui_MessageBubble.h"

MessageBubble::MessageBubble(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageBubble)
{
    ui->setupUi(this);
}

MessageBubble::~MessageBubble()
{
    delete ui;
}
