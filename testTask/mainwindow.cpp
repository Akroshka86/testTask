#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    // Инициализация указателей
    ui(new Ui::MainWindow),
    db(QSqlDatabase::addDatabase("QSQLITE")),
    query(new QSqlQuery(db)),
    model(new QSqlTableModel(this, db)),
    initialModel(new QSqlTableModel(this, db)),
    nameDelegate(new NameDelegate(this)),
    dateDelegate(new DateDelegate(this)),
    phoneDelegate(new PhoneDelegate(this))
{
    // Инициализация интерфейса
    ui->setupUi(this);

    // Установка имени базы данных
    db.setDatabaseName(".telephoneBook.db");

    // Открытие базы данных
    if(db.open())
    {
        qDebug("open");
    }
    else
    {
        qDebug("no open");
    }

    // Создание таблицы в базе данных
    query -> exec("CREATE TABLE TelephoneBook(ID INT, Фамилия TEXT, Имя TEXT, Отчество TEXT, Email TEXT, Дата_рождения DATE, Дата_внесения DATE, Телефон INT);");

    // Загружаем данные из БД ("TelephoneBook")
    model -> setTable("TelephoneBook");
    model -> select();

    // Загружаем данные как копию (для реализации функции возврат)
    initialModel -> setTable("TelephoneBook");
    initialModel -> select();

    // Связываем модель данных с таблицей интерфейса (виджетом)
    ui -> tableView -> setModel(model);

    // Кол-во строк в момент инициализации БД
    initialRowCount = model->rowCount();

    // Функция для соединения сигнала и слота(функции)
    // connect(&на объект который дает сигнал, сигнал который связан с слотом,
    //          &на объект который содержит слот, слот который вызывается)
    connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::sortByColumn);

    // Устанавливаем делегат для определенного столбца
    ui->tableView->setItemDelegateForColumn(1, nameDelegate);
    ui->tableView->setItemDelegateForColumn(2, nameDelegate);
    ui->tableView->setItemDelegateForColumn(3, nameDelegate);
    ui->tableView->setItemDelegateForColumn(5, dateDelegate);
    ui->tableView->setItemDelegateForColumn(6, dateDelegate);
    ui->tableView->setItemDelegateForColumn(7, phoneDelegate);
    ui->tableView->setItemDelegateForColumn(0, phoneDelegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Функция добавления новой строки
void MainWindow::on_addRowButton_clicked()
{
    model -> insertRow(model -> rowCount());
}

// Функция удаления строки
void MainWindow::on_deleteRowButton_clicked()
{
    model -> removeRow(row);
}

// Функция для определения выбранной строки
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

// Функция для сортировки столбцов
void MainWindow::sortByColumn(int column)
{
    // Получаем текущий порядок сортировки для столбца
    Qt::SortOrder currentOrder = sortOrders.value(column, Qt::AscendingOrder);

    // Меняем порядок сортировки на противоположный
    Qt::SortOrder newOrder = (currentOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;

    // Применяем новый порядок сортировки к модели данных
    model->setSort(column, newOrder);
    model->select();

    // Сохраняем новый порядок сортировки для столбца
    sortOrders[column] = newOrder;
}

// Функция кнопки возврат
void MainWindow::on_refundButton_clicked()
{
    // Отмена всех изменений
    model->revertAll();

    // Удаление всех строк, добавленных после загрузки данных
    int currentRowCount = model->rowCount();
    for (int i = currentRowCount - 1; i >= initialRowCount; --i) {
        model->removeRow(i);
    }

    // Восстановление модели данных к изначальному состоянию
    initialModel->select();
    model->setTable("TelephoneBook");
    model->select();

}

// Функция кнопки поиска
void MainWindow::on_searchButton_clicked()
{
    QString searchText = ui->lineEdit->text();
    search(searchText);
}

// Функция поиска
void MainWindow::search(const QString &text)
{
    // Если текст поиска пустой, показываем все записи
    if (text.isEmpty()) {
        model->setFilter("");
    }
    else
    {
        // Установка фильтра для модели данных для строгого поиска
        QString filter = QString("(ID = '%1' OR Фамилия = '%1' OR Имя = '%1' OR Отчество = '%1' OR Email = '%1' OR Дата_рождения = '%1' OR Дата_внесения = '%1' OR Телефон = '%1')").arg(text);
        model->setFilter(filter);
    }
    model->select();
}







