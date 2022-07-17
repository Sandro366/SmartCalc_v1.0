#include "variable_x.h"
#include "ui_variable_x.h"

variable_X::variable_X(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::variable_X)
{
    ui->setupUi(this);
    connect(ui->button_0, SIGNAL(clicked()), this, SLOT(numbers_click()));
    connect(ui->button_1, SIGNAL(clicked()), this, SLOT(numbers_click()));
    connect(ui->button_2, SIGNAL(clicked()), this, SLOT(numbers_click()));
    connect(ui->button_3, SIGNAL(clicked()), this, SLOT(numbers_click()));
    connect(ui->button_4, SIGNAL(clicked()), this, SLOT(numbers_click()));
    connect(ui->button_5, SIGNAL(clicked()), this, SLOT(numbers_click()));
    connect(ui->button_6, SIGNAL(clicked()), this, SLOT(numbers_click()));
    connect(ui->button_7, SIGNAL(clicked()), this, SLOT(numbers_click()));
    connect(ui->button_8, SIGNAL(clicked()), this, SLOT(numbers_click()));
    connect(ui->button_9, SIGNAL(clicked()), this, SLOT(numbers_click()));
    connect(ui->button_dot, SIGNAL(clicked()), this, SLOT(dot_click()));
    connect(ui->button_abs, SIGNAL(clicked()), this, SLOT(button_abs_click()));
    connect(ui->button_C, SIGNAL(clicked()), this, SLOT(button_clear()));
    connect(ui->button_back, SIGNAL(clicked()), this, SLOT(button_back_click()));
    connect(ui->button_ok, SIGNAL(clicked()), this, SLOT(button_ok_click()));
}

variable_X::~variable_X() {delete ui;}

void variable_X::numbers_click() {
  QPushButton *button = (QPushButton *)sender();
  QString temp = button->text();
  QString str = ui->monitor->text();
  int length = str.length();
  if (str.isEmpty()) {ui->monitor->setText(str + temp);}
  else {
      QChar ch = str[length - 1];
      if (ch.isDigit() && ch != '0') {
          ui->monitor->setText(str + temp);
      } else {
          if (length > 1) {
              if (str[length - 2].isDigit() || str[length - 2] == '.') ui->monitor->setText(str + temp);
          }
      }
  }
}

void variable_X::dot_click() {
    QString str = ui->monitor->text();
    int flag_dot = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '.') {
            flag_dot = 1;
            break;
        }
    }
    if(flag_dot == 0 && !str.isEmpty()) {
        ui->monitor->setText(ui->monitor->text() + ".");
    }
}

void variable_X::button_back_click() {
    QString str = ui->monitor->text();
    if (str.isEmpty()) {
        str = "";
    } else {
        str.chop(1);
    }
    ui->monitor->setText(str);
}

void variable_X::button_abs_click() {
    QString str = ui->monitor->text();
    if (!str.isEmpty() && str != "-") {
        double value = str.toDouble();
        value = -value;
        str = QString::number(value, 'g', 10);
    } else if (str == "-") {
        str = "";
    } else {
        str = "-";
    }
    ui->monitor->setText(str);
}

void variable_X::button_clear() {
    ui->monitor->setText("");
}

void variable_X::button_ok_click() {
    QString str = ui->monitor->text();
    if (!str.isEmpty()) {
      double x = str.toDouble();
      emit give_x(x);
      close();
    }
}
