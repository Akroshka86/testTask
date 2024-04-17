#include "phonedelegate.h"
#include <QLineEdit>
#include <QRegularExpressionValidator>

PhoneDelegate::PhoneDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

QWidget *PhoneDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QLineEdit *editor = new QLineEdit(parent);
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("[0-9\\p{P} ]+"), editor);
    editor->setValidator(validator);
    return editor;
}
