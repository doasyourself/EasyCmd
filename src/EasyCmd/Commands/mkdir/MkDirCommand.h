#ifndef MKDIRCOMMAND_H
#define MKDIRCOMMAND_H

#include "IUnifiedBase.h"
#include "CommandGlobal.h"
#include "ICmdEditor.h"

class COMMAND_API MkDirCommand : public IUnifiedBase
{
    Q_OBJECT
    Q_INTERFACES(IUnifiedBase)
    Q_PLUGIN_METADATA(IID "com.qtfuture.easycmd.mkdir-command")

public:
    explicit MkDirCommand(QObject *parent = nullptr);

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);
};

#endif // MKDIRCOMMAND_H
