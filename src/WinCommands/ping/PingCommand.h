#ifndef PINGCOMMAND_H
#define PINGCOMMAND_H

#include "IUnifiedBase.h"
#include "CommonGlobal.h"
#include "ICmdEditor.h"
#include "PingCommandGlobal.h"

class PINGCOMMAND_API PingCommand : public IUnifiedBase
{
    Q_OBJECT
    Q_INTERFACES(IUnifiedBase)
    Q_PLUGIN_METADATA(IID "com.qtfuture.easycmd.ping-command")

public:
    explicit PingCommand(QObject *parent = nullptr);

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);
};

#endif // PINGCOMMAND_H
