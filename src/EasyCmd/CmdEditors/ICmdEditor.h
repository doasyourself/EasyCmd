#ifndef ICMDEDITOR_H
#define ICMDEDITOR_H

#include <QString>
#include <QWidget>

class ICmdEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ICmdEditor(QWidget *parent = NULL);

    virtual bool isModified() const = 0;
    virtual QString getCmdString() = 0;

signals:
    void sigModified();
};

#endif // ICMDEDITOR_H
