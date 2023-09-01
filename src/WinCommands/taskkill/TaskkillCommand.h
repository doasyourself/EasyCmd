#ifndef TASKKILLCOMMAND_H
#define TASKKILLCOMMAND_H

#include "IUnifiedBase.h"
#include "CommonGlobal.h"
#include "ICmdEditor.h"
#include "TaskkillCommandGlobal.h"

class TASKKILLCOMMAND_API TaskkillCommand : public IUnifiedBase
{
    Q_OBJECT
    Q_INTERFACES(IUnifiedBase)
    Q_PLUGIN_METADATA(IID "com.qtfuture.easycmd.taskkill-command")

public:
    explicit TaskkillCommand(QObject *parent = nullptr);

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);
};

#endif // TASKKILLCOMMAND_H
