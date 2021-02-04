#ifndef CmdProxyModel_H
#define CmdProxyModel_H

#include <QSortFilterProxyModel>

class CmdProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit CmdProxyModel(QObject *parent = 0);

protected:
    /**
     * @brief filterAcceptsRow
     *  实现对所有层的树节点进行遍历，默认只遍历一层
     * @param source_row
     * @param source_parent
     * @return
     */
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // CmdProxyModel_H
