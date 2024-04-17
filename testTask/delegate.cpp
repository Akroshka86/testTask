#include "delegate.h"
#include <QLineEdit>
#include <QRegularExpressionValidator>

NameDelegate::NameDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

QWidget *NameDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QLineEdit *editor = new QLineEdit(parent);
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("[А-Яа-яA-Za-zЁё-]+"), editor);
    editor->setValidator(validator);
    return editor;
}



