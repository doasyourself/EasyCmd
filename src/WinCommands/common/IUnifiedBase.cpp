#include "IUnifiedBase.h"

IUnifiedBase::IUnifiedBase(QObject *parent) : QObject(parent)
{
}

int IUnifiedBase::getProperty(int propertyId, QVariant &out_property)
{
    int code = 0;
    return code;
}

int IUnifiedBase::setProperty(int propertyId, const QVariant &property)
{
    int code = 0;
    return code;
}

void IUnifiedBase::slotOnNotify(int type, const QVariantHash &val)
{

}
