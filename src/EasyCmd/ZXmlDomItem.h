#ifndef ZXMLDOMITEM_H
#define ZXMLDOMITEM_H

#include <QDomNode>
#include <QHash>

class ZXmlDomItem
{
public:
    ZXmlDomItem(QDomNode &node, ZXmlDomItem *parent = NULL);
    ~ZXmlDomItem();

    // 获取子指定行的节点
    ZXmlDomItem *child(int i) const;

    // 获取父节点
    ZXmlDomItem *parent() const;

    // 获取文档节点数据
    QDomNode node() const;

    // 获取此节点所在行数
    int row();

    // 获取子节点个数
    int rowCount() const;

private:
    // 文档节点
    QDomNode m_dom_node;

    // 子节点集合
    QList<ZXmlDomItem *> m_child_items;

    // 父节点
    ZXmlDomItem *m_parent_item;

    // 行号
    int m_row;
};

#endif // ZXMLDOMITEM_H
