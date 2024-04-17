#ifndef DELEGATE_H
#define DELEGATE_H


#include <QStyledItemDelegate>

class NameDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit NameDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
};





#endif // DELEGATE_H
