#ifndef VARIABLE_X_H
#define VARIABLE_X_H

#include <QWidget>

namespace Ui {
class variable_X;
}

class variable_X : public QWidget
{
    Q_OBJECT

public:
    explicit variable_X(QWidget *parent = nullptr);
    ~variable_X();

signals:
  void give_x(double x);

private slots:
  void numbers_click();
  void dot_click();
  void button_back_click();
  void button_abs_click();
  void button_clear();
  void button_ok_click();

private:
    Ui::variable_X *ui;
};

#endif // VARIABLE_X_H
