#include "CmdTreeModel.h"
#include <QFile>
#include <QMessageBox>

CmdTreeModel::CmdTreeModel(QDomDocument dom,  QObject *parent)
    : QAbstractItemModel(parent)
{
    m_doc = dom;
    m_root_item = new ZXmlDomItem(m_doc);
}

QVariant CmdTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        QString name;
        switch (section)
        {
        case COL_COMMAND:
        {
            name = tr("Command");
            break;
        }
        case COL_CMDDESC:
        {
            name = tr("Command Desc");
        }
        default:
        {
            break;
        }
        }

        return name;
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}

QModelIndex CmdTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    ZXmlDomItem *parentItem;

    // 获取父节点
    if (!parent.isValid())
        parentItem = m_root_item;
    else
        parentItem = static_cast<ZXmlDomItem*>(parent.internalPointer());

    // 获取子节点，生成索引
    ZXmlDomItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();

    return QModelIndex();
}

QModelIndex CmdTreeModel::parent(const QModelIndex &index) const
{
    ZXmlDomItem *item = static_cast<ZXmlDomItem*>(index.internalPointer());
    ZXmlDomItem *parent_item = item->parent();

    if (item == m_root_item || parent_item == m_root_item)
      return QModelIndex();

    return createIndex(parent_item->row(), 0, parent_item);
}

int CmdTreeModel::rowCount(const QModelIndex &parent) const
{
    // 获取此节点Item
    ZXmlDomItem *parent_item;
    if (!parent.isValid())
    {
        parent_item = m_root_item;
    }
    else
    {
        parent_item = static_cast<ZXmlDomItem *>(parent.internalPointer());
    }

    return parent_item->rowCount();
}

int CmdTreeModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant CmdTreeModel::data(const QModelIndex &index, int role) const
{
    QVariant v;

    do
    {
        if (!index.isValid()) break;

        ZXmlDomItem *item = static_cast<ZXmlDomItem *>(index.internalPointer());
        QDomNode node = item->node();
        if (role == Qt::DisplayRole)
        {
            switch (index.column())
            {
            case COL_COMMAND:
            {
                v = node.attributes().namedItem("name").nodeValue();
                break;
            }
            case COL_CMDDESC:
            {
                v = node.attributes().namedItem("desc").nodeValue();
                break;
            }
            default:
            {
                break;
            }
            }
        }
        else if (role == Qt::UserRole) /*获取id，英文*/
        {
            v = node.attributes().namedItem("id").nodeValue();
        }

    } while (0);

    return v;
}

CmdTreeModel *CmdTreeModel::modelFromFile(const QString &filepath)
{
    CmdTreeModel *model = NULL;
    bool xml_ok = false;
    QDomDocument doc;

    QFile file(filepath);
    if (file.open(QFile::ReadOnly))
    {
        QString xml_error_info;
        int error_line, error_col;
        if (!doc.setContent(&file, &xml_error_info, &error_line, &error_col))
        {
            QString error_string = tr("Parse XML file failed, error string: %1, %2 row, %3 col")
                    .arg(xml_error_info)
                    .arg(error_line)
                    .arg(error_col);

            QMessageBox::information(0, tr("Error"), error_string);
            xml_ok = false;
        }
        else
        {
            xml_ok = true;
        }

        file.close();
    }
    else
    {
        QString error_string = tr("Open file %1 failed: %2")
                .arg(filepath).arg(file.errorString());
        QMessageBox::information(0, tr("Error"), error_string);
        xml_ok = false;
    }

    if (xml_ok)
    {
        model = new CmdTreeModel(doc);
    }

    return model;
}
