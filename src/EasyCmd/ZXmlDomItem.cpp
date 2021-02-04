#include "ZXmlDomItem.h"
#include <QDebug>

ZXmlDomItem::ZXmlDomItem(QDomNode &node, ZXmlDomItem *parent)
{
    m_dom_node = node.isDocument() ? node.toDocument().documentElement() : node;/*排除xml标签*/
    m_parent_item = parent;

    // 创建/更新子节点列表
    QDomNodeList child_node_list = m_dom_node.childNodes();
    int child_count = child_node_list.count();
    for (int i = 0; i < child_count; i++)
    {
        QDomNode childNode = child_node_list.item(i);
        ZXmlDomItem *childItem = new ZXmlDomItem(childNode, this);
        m_child_items.append(childItem);
    }
}

ZXmlDomItem::~ZXmlDomItem()
{
    qDeleteAll(m_child_items.begin(), m_child_items.end());
}

ZXmlDomItem *ZXmlDomItem::child(int i) const
{
    return m_child_items.value(i);
}

ZXmlDomItem *ZXmlDomItem::parent() const
{
    return m_parent_item;
}

QDomNode ZXmlDomItem::node() const
{
    return m_dom_node;
}

int ZXmlDomItem::row()
{
    if (m_parent_item)
    {
        return m_parent_item->m_child_items.indexOf(this);
    }
    else
    {
        return 0;
    }
}

int ZXmlDomItem::rowCount() const
{
    return m_child_items.count();
}
