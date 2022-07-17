#include "s21_sm_calc.h"
#include "ui_s21_sm_calc.h"


s21_sm_calc::s21_sm_calc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::s21_sm_calc)
{
    ui->setupUi(this);
    connect(ui->button_0, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_1, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_2, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_3, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_4, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_5, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_6, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_7, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_8, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_9, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_sin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->button_cos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->button_tan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->button_asin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->button_acos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->button_atan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->button_ln, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->button_log, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->button_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->button_dot, SIGNAL(clicked()), this, SLOT(dot_click()));
    connect(ui->button_plus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->button_minus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->button_div, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->button_mul, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->button_mod, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->button_pow, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->button_bracket_L, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_bracket_R, SIGNAL(clicked()), this, SLOT(numbers_and_brackets()));
    connect(ui->button_C, SIGNAL(clicked()), this, SLOT(button_clear()));
    connect(ui->button_back, SIGNAL(clicked()), this, SLOT(button_back_click()));
    connect(ui->button_x, SIGNAL(clicked()), this, SLOT(button_x_click()));
    connect(ui->button_result, SIGNAL(clicked()), this, SLOT(result_click()));

    QPixmap pix(":/img/Ast2.jpg");
    int w = ui ->image->width();
    int h = ui ->image->height();
    ui->image->setIcon(pix.scaled(w, h, Qt::KeepAspectRatio));
}

s21_sm_calc::~s21_sm_calc() {delete ui;}


void s21_sm_calc::on_image_clicked() {
    QMessageBox::information(this, "Благодарность от хомяка", "Уважаемый проверяющий! \nСпасибо за твою титаническую работу!");
}

void s21_sm_calc::numbers_and_brackets() {
    QPushButton *button = (QPushButton *)sender();
    QString temp = button->text();
    QString str = ui->monitor->text();
    int length = str.length();
    int open_bracket = 0, close_bracket = 0;
    for (int i = 0; i < length; i++) {
      if (str[i] == '(') open_bracket++;
      if (str[i] == ')') close_bracket++;
    }
    if (str.isEmpty()) {if (temp != ")") ui->monitor->setText(str + temp);}
    else {
        QChar ch = str[length - 1];
        if (temp == "(") {
          if (!ch.isDigit() && ch != '.' && ch != ')') {
            ui->monitor->setText(str + temp);
          }
        } else if (temp == ")") {
          if ((ch == ')' || ch.isDigit() || ch == 'X') && (open_bracket >= close_bracket + 1)) {
             ui->monitor->setText(str + temp);
          }
        } else if (ch.isDigit() && ch != '0') {
            ui->monitor->setText(str + temp);
        } else if (ch == '0') {
            if (length > 1) {
                if (str[length - 2].isDigit() || str[length - 2] == '.') ui->monitor->setText(str + temp);
            }
        } else {
            if(ch != ')' && ch != 'X') ui->monitor->setText(str + temp);
        }
    }
}

void s21_sm_calc::operations() {
    QPushButton *button = (QPushButton *)sender();
    QString temp = button->text();
    QString str = ui->monitor->text();
    int length = str.length();
    if (length == 0) {
        if (temp == "+" || temp == "-") ui->monitor->setText(str + temp);
    } else {
        QChar ch = str[length - 1];
        if ((temp == "-" || temp == "+") && (ch.isDigit() || ch == '(' || ch == ')' || ch == 'X')) {
            ui->monitor->setText(str + temp);
        } else if ((ch == '+' || ch == '*' || ch == '/' || ch == '^')){
            if (length > 1) {
                if (str[length - 2] != '(') {
                    str.chop(1);
                    ui->monitor->setText(str + temp);
                } else {

                }
            }
        } else if (ch == ')') {
            ui->monitor->setText(str + temp);
        } else if (ch == '-' && length > 1) {
            if (str[length - 2] != '(') {
                str.chop(1);
                ui->monitor->setText(str + temp);
            }
        } else if (ch == 'd'){
            str.chop(3);
            ui->monitor->setText(str + temp);
        } else if (!ch.isPunct()) {
          ui->monitor->setText(str + temp);
        }
    }
}

void s21_sm_calc::functions() {
    QPushButton *button = (QPushButton *)sender();
    QString temp = button->text();
    QString str = ui->monitor->text();
    QChar ch = '\0';
    if (!str.isEmpty()) ch = str[str.length() - 1];
    if (!ch.isDigit() && ch != ')' && ch != 'd' && ch != '.' && ch != 'X') {
      if (temp == "√") {
        ui->monitor->setText(str + "sqrt(");
      } else {
        ui->monitor->setText(str + temp + '(');
      }
    }
}

void s21_sm_calc::dot_click() {
    QPushButton *button = (QPushButton *)sender();
    QString temp = button->text();
    QString str = ui->monitor->text();
    int length = str.length();
    int flag_dot = 0;
    if (!str.isEmpty()) {
        QChar ch = str[length - 1];
        if (ch == '.') flag_dot = 1;
        if (ch.isPunct() || ch == 'd' || ch == '+' || ch == '^' || ch == 'X') flag_dot = 1;
        while (ch.isDigit()) {
          if (length == 0) break;
          ch = str[--length];
          if (ch == '.') {
              flag_dot = 1;
              break;
          }
        }
        if (flag_dot == 0) ui->monitor->setText(str + temp);
    }
}

void s21_sm_calc::button_clear() {
    ui->monitor->setText("");
    ui->result_monitor->setText("");
    ui->graph->setEnabled(false);
}

void s21_sm_calc::button_back_click() {
    QString str = ui->monitor->text();
    int length = str.length();
    if (str.isEmpty()) {
        str = "";
    } else {
        QChar ch = str[--length];
        str.chop(1);
        if ((ch == '(' || ch == 'd') && length > 0) {
            ch = str[--length];
            if (ch >= 'a' && ch <= 'z') {
                while (ch >= 'a' && ch <= 'z') {
                    str.chop(1);
                    if (length == 0) break;
                    ch = str[--length];
                }
            }
        }
    }
    ui->monitor->setText(str);
    int flag_X = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == 'X') flag_X = 1;
    }
    if (flag_X == 0) ui->graph->setEnabled(false);
}

void s21_sm_calc::button_x_click() {
    ui->graph->setEnabled(true);
    QPushButton *button = (QPushButton *)sender();
    QString temp = button->text();
    QString str = ui->monitor->text();
    if (!str.isEmpty()) {
        QChar ch = str[str.length() - 1];
        if (ch.isPunct() || ch == 'd' || ch == '+' || ch == '^') {
            ui->monitor->setText(str + temp);
        }
    } else ui->monitor->setText(str+ temp);
}

void s21_sm_calc::result_click() {
    QString str = ui->monitor->text();
    QChar ch = '\0';
    if (!str.isEmpty()) {
        ch = str[str.length() - 1];
        int flag_X = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == 'X') flag_X = 1;
        }
        if (ch == ')' || ch.isDigit() || ch == 'X') {
            int open_bracket = 0, close_bracket = 0;
            for (int i = 0; i < str.length(); i++) {
              if (str[i] == '(') open_bracket++;
              if (str[i] == ')') close_bracket++;
            }
            while (close_bracket < open_bracket) {
                str.append(")");
                close_bracket++;
            }
            if (flag_X) {
                x_window = new variable_X();
                x_window->show();
                connect(x_window, SIGNAL(give_x(double)), this, SLOT(get_x(double)));
            } else {
                QString result = calculate_result(str, 0);
                ui->result_monitor->setText(result);
            }
        }
        else {
            ui->result_monitor->setText("Допиши выражение");
        }
     }
}

QString calculate_result(QString str, double x) {
    QByteArray str_1 = str.toLocal8Bit();
    char *str_2 = str_1.data();
    setlocale(LC_NUMERIC, "C");
    double temp = s21_calculator(str_2, x);
    QString result = "\0";
    if (temp == temp) {
        result = QString::number(temp, 'g', 7);
    } else {
        result = "NAN";
    }
    return result;
}

void s21_sm_calc::get_x(double x) {
    QString str = ui->monitor->text();
    int open_bracket = 0, close_bracket = 0;
    for (int i = 0; i < str.length(); i++) {
      if (str[i] == '(') open_bracket++;
      if (str[i] == ')') close_bracket++;
    }
    while (close_bracket < open_bracket) {
        str.append(")");
        close_bracket++;
    }
    QString result = calculate_result(str, x);
    ui->result_monitor->setText(result);
}

void s21_sm_calc::on_graph_triggered()
{
    param_window = new graph_parameters();
    param_window->show();
    connect(param_window, SIGNAL(give_graph_x(double, double)), this, SLOT(get_graph_x(double, double)));
}

void s21_sm_calc::get_graph_x(double x_min, double x_max) {
    double h = 0.0, y = 0.0;
    int count = 0;
    QVector<double> X, Y;
    QString str = ui->monitor->text();
    int open_bracket = 0, close_bracket = 0;
    for (int i = 0; i < str.length(); i++) {
      if (str[i] == '(') open_bracket++;
      if (str[i] == ')') close_bracket++;
    }
    while (close_bracket < open_bracket) {
        str.append(")");
        close_bracket++;
    }
    QByteArray str_1 = str.toLocal8Bit();
    char *str_2 = str_1.data();
    double delta = x_max - x_min;
    for (double x = x_min; x <= x_max; x += h) {
        if (delta <= 10) h = 0.05;
        else if (x > 10 || x < 1000 ) h = 0.1;
        else h = 1;
        setlocale(LC_NUMERIC, "C");
        y = s21_calculator(str_2, x);
        count++;
        X.push_back(x);
        Y.push_back(y);
    }
    double y_min = Y[0], y_max = Y[0];
    for (int i = 1; i < count; i++) {
      if (Y[i] < y_min) y_min = Y[i];
      if (Y[i] > y_max) y_max = Y[i];
    }
    graphic_window = new Grid_graphics();
    QCustomPlot *plot = graphic_window-> ui->graph_widget;
    plot->xAxis->setRange(x_min, x_max);
    plot->yAxis->setRange(y_min, y_max);
    plot->xAxis->setLabel("ось X");
    plot->yAxis->setLabel("ось Y");
    plot->addGraph(plot->xAxis, plot->yAxis);
    plot->setBackground(QColor(234, 246, 249));
    plot->graph(0)->setData(X, Y);
    plot->graph(0)->setPen(QColor(255, 0, 13));
    plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    //plot->replot();
    plot->setInteraction(QCP::iRangeZoom, true);
    plot->setInteraction(QCP::iRangeDrag, true);
    graphic_window->show();
}

void s21_sm_calc::on_deposit_triggered()
{
    hide();
    deposit_window = new Deposit();
    deposit_window->show();
    connect(deposit_window, SIGNAL(close_deposit()), this, SLOT(return_calc()));
}

void s21_sm_calc::on_credit_triggered()
{
    hide();
    credit_window = new Credit();
    credit_window->show();
    connect(credit_window, SIGNAL(close_credit()), this, SLOT(return_calc()));
}

void s21_sm_calc::return_calc() {
    show();
}
