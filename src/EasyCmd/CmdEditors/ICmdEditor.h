#ifndef ICMDEDITOR_H
#define ICMDEDITOR_H

#include <QString>

class ICmdEditor
{
public:
    ICmdEditor();

    virtual bool isModified() const = 0;
    virtual QString getCmdString() = 0;
};

#endif // ICMDEDITOR_H
