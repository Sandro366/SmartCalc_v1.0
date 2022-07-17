#include "graph_parameters.h"
#include "ui_graph_parameters.h"

graph_parameters::graph_parameters(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graph_parameters)
{
    ui->setupUi(this);
}

graph_parameters::~graph_parameters() {
    delete ui;
}

void graph_parameters::on_button_back_clicked() {
    close();
}

void graph_parameters::on_button_ok_clicked() {
    int flag = 1;
    QString str_min, str_max;
    str_min = ui->x_min_line->text();
    str_max = ui->x_max_line->text();
    if (str_min.isEmpty() || str_max.isEmpty()) {flag = 0;}
    if (flag) {
        if (!verification(str_min) || !verification(str_max)) {flag = 0;}
    }
    if (flag) {
        double x_min, x_max;
        x_min = str_min.toDouble();
        x_max = str_max.toDouble();
        if (x_min < -1000000) x_min = -1000000;
        if (x_max > 1000000) x_max = 1000000;
        if (x_min > x_max) {
            int temp = x_min;
            x_min = x_max;
            x_max = temp;
        }
        emit give_graph_x(x_min, x_max);
        close();
    } else {
        ui->label_error->setText("Некорректный ввод! Повтори, дружок!");
    }
}

int verification(QString str) {
    int flag = 1;
    int dot_count = 0;
    for (int i = 0; i < str.length(); i++) {
        QChar ch = str[i];
        if(!ch.isDigit() && ch != '.' && ch !='-') {flag = 0; break;}
        if(i == 0 && ch == '.') {flag = 0; break;}
        if(ch == '-' && i != 0) {flag = 0; break;}
        if (ch == '.') dot_count++;
    }
    if (str.length() > 2) {
        if (str[0] == '-' && str[1] == '0' && str[2] != '.') flag = 0;
    }
    if (str.length() > 1) {
        if ((str[0] == '0' && str[1] != '.') || (str[0] == '-' && str[1] == '.')) flag = 0;
    }
    if (dot_count > 1) flag = 0;
    return flag;
}

int verification_digit(QString str) {
    int flag = 1;
    if (!str.isEmpty()) {
        for (int i = 0; i < str.length(); i++) {
            if (!str[i].isDigit()) {flag = 0; break;}
        }
    } else flag = 0;
    return flag;
}
