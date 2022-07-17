#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>
#include "graph_parameters.h"

namespace Ui {
class Credit;
}

class Credit : public QWidget
{
    Q_OBJECT

public:
    explicit Credit(QWidget *parent = nullptr);
    ~Credit();

signals:
    void close_credit();

private slots:
    void on_button_back_clicked();
    void on_button_OK_clicked();

private:
    Ui::Credit *ui;
};


#endif // CREDIT_H
