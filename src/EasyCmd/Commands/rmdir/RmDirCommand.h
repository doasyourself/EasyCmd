#ifndef RMDIRCOMMAND_H
#define RMDIRCOMMAND_H

#include "IUnifiedBase.h"
#include "CommandGlobal.h"
#include "ICmdEditor.h"

class COMMAND_API RmDirCommand : public IUnifiedBase
{
    Q_OBJECT
    Q_INTERFACES(IUnifiedBase)
    Q_PLUGIN_METADATA(IID "com.qtfuture.easycmd.rmdir-command")
public:
    explicit RmDirCommand(QObject *parent = nullptr);

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);
};

#endif // RMDIRCOMMAND_H
