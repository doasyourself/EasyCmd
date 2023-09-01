#ifndef IUNIFIEDBASE_H
#define IUNIFIEDBASE_H

/*******************************************************************************
** 缂佺喍绔撮幒銉ュ經
**
**
*******************************************************************************/

#include <QObject>
#include <QVariantHash>
#include "CommonGlobal.h"

class COMMON_API IUnifiedBase : public QObject
{
    Q_OBJECT

public:
    explicit IUnifiedBase(QObject *parent = nullptr);

    /**
     * @brief getProperty
     * @param propertyId
     * @param out
     * @return
     */
    virtual int getProperty(int propertyId, QVariant &out_property);

    /**
     * @brief setProperty
     * @param propertyId
     * @param property
     * @return
     */
    virtual int setProperty(int propertyId, const QVariant &property);

public slots:
    /**
     * @brief slotOnNotify
     *  响应通知
     */
    virtual void slotOnNotify(int type, const QVariantHash &val);

signals:
    /**
     * @brief sigNotify
     *  发出通知
     */
    void sigNotify(int type, const QVariantHash &val);
};

#define IUnifiedBase_iid "com.qtfuture.easycmd.iunifiedbase"
Q_DECLARE_INTERFACE(IUnifiedBase, IUnifiedBase_iid);

// make it known to QVariant
Q_DECLARE_METATYPE(void *);

#endif // IUNIFIEDBASE_H
