#ifndef ICMDEDITOR_H
#define ICMDEDITOR_H

/*******************************************************************************
** 编辑器基类。
** 编辑器设计原则：
** 1.编辑器不可使用对话框，否则会频繁弹出重复的信息，而且不能持续显示。
** 2.多使用QGroupBox，此控件自带选中功能
** 3.出现错误也要继续，不然后面的配置会不显示
** 4.选项即使没有值，也属于有此选项，所以需要用QCheckBox显式指定每个选项，虽然多了一步点击。
**  但是更清楚，不隐晦。列表除外。
** 5.采用通知->查询的方式进行更新。
********************************************************************************/

#include <QString>
#include <QWidget>
#include <QVariantHash>

class ICmdEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ICmdEditor(QWidget *parent = NULL);

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
    void sigNotify(int type, QVariantHash val);
};

#endif // ICMDEDITOR_H
