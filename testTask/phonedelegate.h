#ifndef PHONEDELEGATE_H
#define PHONEDELEGATE_H


#include <QStyledItemDelegate>

class PhoneDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit PhoneDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
};

#endif // PHONEDELEGATE_H
