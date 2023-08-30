#ifndef IPCONFIGCOMMAND_H
#define IPCONFIGCOMMAND_H

#include "IUnifiedBase.h"
#include "CommandGlobal.h"
#include "ICmdEditor.h"

class COMMAND_API IPConfigCommand : public IUnifiedBase
{
    Q_OBJECT
    Q_INTERFACES(IUnifiedBase)
    Q_PLUGIN_METADATA(IID "com.qtfuture.easycmd.ipconfig-command")

public:
    explicit IPConfigCommand(QObject *parent = nullptr);

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);
};

#endif // IPCONFIGCOMMAND_H
