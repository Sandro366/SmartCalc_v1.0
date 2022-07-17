#ifndef GRAPH_PARAMETERS_H
#define GRAPH_PARAMETERS_H

#include <QWidget>

namespace Ui {
class graph_parameters;
}

class graph_parameters : public QWidget
{
    Q_OBJECT

public:
    explicit graph_parameters(QWidget *parent = nullptr);
    ~graph_parameters();

signals:
    void give_graph_x(double x_min, double x_max);

private slots:
    void on_button_back_clicked();
    void on_button_ok_clicked();

private:
    Ui::graph_parameters *ui;
};

int verification(QString str);
int verification_digit(QString str);

#endif // GRAPH_PARAMETERS_H
