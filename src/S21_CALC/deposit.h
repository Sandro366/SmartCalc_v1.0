#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>
#include <QDate>
#include "graph_parameters.h"

namespace Ui {
class Deposit;
}

class Deposit : public QWidget
{
    Q_OBJECT

public:
    explicit Deposit(QWidget *parent = nullptr);
    ~Deposit();

signals:
    void close_deposit();

private slots:
    void on_button_back_clicked();
    void on_button_OK_clicked();
    void on_Box_vyplaty_activated(int index);
    void on_Box_popoln_activated(int index);
    void on_Box_snyat_activated(int index);

private:
    Ui::Deposit *ui;
    int index_vyp;
    int index_pop;
    int index_snyat;
};

QDate date_now_add(QDate date_now, int index);
QDate date_vyplat_index(QDate date_now, int index);

#endif // DEPOSIT_H
