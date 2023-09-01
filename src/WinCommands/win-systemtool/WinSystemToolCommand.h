#ifndef WINSYSTEMTOOLCOMMAND_H
#define WINSYSTEMTOOLCOMMAND_H

#include "IUnifiedBase.h"
#include "CommonGlobal.h"
#include "ICmdEditor.h"
#include "WinSystemToolCommandGlobal.h"

class WINSYSTEMTOOLCOMMAND_API WinSystemToolCommand : public IUnifiedBase
{
    Q_OBJECT
    Q_INTERFACES(IUnifiedBase)
    Q_PLUGIN_METADATA(IID "com.qtfuture.easycmd.winsystemtool-command")

public:
    explicit WinSystemToolCommand(QObject *parent = nullptr);

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);
};

#endif // WINSYSTEMTOOLCOMMAND_H
