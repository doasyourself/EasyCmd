#ifndef CMDTREEMODEL_H
#define CMDTREEMODEL_H

#include <QAbstractItemModel>
#include <QDomDocument>

#include "ZXmlDomItem.h"

class CmdTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum
    {
        COL_COMMAND = 0/*命令*/,
        COL_CMDDESC/*命令描述*/
    };

public:
    explicit CmdTreeModel(QDomDocument dom, QObject *parent = nullptr);

    static CmdTreeModel *modelFromFile(const QString &filepath);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QDomDocument m_doc;
    ZXmlDomItem  *m_root_item;
};

#endif // CMDTREEMODEL_H
