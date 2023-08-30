#ifndef NETSTATCOMMAND_H
#define NETSTATCOMMAND_H

#include "IUnifiedBase.h"
#include "CommandGlobal.h"
#include "ICmdEditor.h"

class COMMAND_API NetStatCommand : public IUnifiedBase
{
    Q_OBJECT
    Q_INTERFACES(IUnifiedBase)
    Q_PLUGIN_METADATA(IID "com.qtfuture.easycmd.netstat-command")

public:
    explicit NetStatCommand(QObject *parent = nullptr);

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);
};

#endif // NETSTATCOMMAND_H
