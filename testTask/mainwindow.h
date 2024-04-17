#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "delegate.h"
#include "datedelegate.h"
#include "phonedelegate.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // Определяем слоты для реализации нескольких функций
    void on_addRowButton_clicked();
    void on_deleteRowButton_clicked();
    void on_refundButton_clicked();
    void on_searchButton_clicked();

    // Определяем слот, который возвращает индекс элемента,
    // по которому был выполнен щелчок.
    void on_tableView_clicked(const QModelIndex &index);


private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;
    QSqlTableModel *initialModel;
    NameDelegate *nameDelegate;
    DateDelegate *dateDelegate;
    PhoneDelegate *phoneDelegate;
    QMap<int, Qt::SortOrder> sortOrders;

    // Переменная для хранения выбранной строки
    int row;

    // Переменная для хранения начального кол-ва строк
    int initialRowCount;

    // Объявление Функций для сортировки
    void sortByColumn(int column);

    // Объявление функции поиска
    void search(const QString &text);

};
#endif // MAINWINDOW_H
