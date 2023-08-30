#ifndef COPYCOMMAND_H
#define COPYCOMMAND_H

#include "IUnifiedBase.h"
#include "CommandGlobal.h"
#include "ICmdEditor.h"

class COMMAND_API CopyCommand : public IUnifiedBase
{
    Q_OBJECT
    Q_INTERFACES(IUnifiedBase)
    Q_PLUGIN_METADATA(IID "com.qtfuture.easycmd.copy-command")

public:
    explicit CopyCommand(QObject *parent = nullptr);

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);
};

#endif // COPYCOMMAND_H
