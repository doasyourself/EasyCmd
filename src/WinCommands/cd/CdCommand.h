#ifndef CDCOMMAND_H
#define CDCOMMAND_H

#include <QObject>

#include "IUnifiedBase.h"
#include "CommonGlobal.h"
#include "ICmdEditor.h"
#include "CdCommandGlobal.h"

class CDCOMMAND_API CdCommand : public IUnifiedBase
{
    Q_OBJECT
    Q_INTERFACES(IUnifiedBase)
    Q_PLUGIN_METADATA(IID "com.qtfuture.easycmd.cd-command")

public:
    explicit CdCommand(QObject *parent = nullptr);

    virtual int getProperty(int propertyId, QVariant &out_property);
    virtual int setProperty(int propertyId, const QVariant &property);
};

#endif // CDCOMMAND_H
