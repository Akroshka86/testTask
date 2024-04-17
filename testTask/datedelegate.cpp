#include "datedelegate.h"
#include <QDateEdit>

DateDelegate::DateDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

QWidget *DateDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QDateEdit *editor = new QDateEdit(parent);
    editor->setDisplayFormat("dd.MM.yyyy");
    return editor;
}
