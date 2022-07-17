#include "credit.h"
#include "ui_credit.h"

Credit::Credit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);
    ui->result_pay->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->result_proc->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->result_pay_proc->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

Credit::~Credit() {
    delete ui;
}

void Credit::on_button_back_clicked() {
    emit close_credit();
    close();
}


void Credit::on_button_OK_clicked() {
    QString credit_summa = ui->Summa_credit_lab->text();
    QString credit_time = ui->Time_credit_lab->text();
    QString credit_stavka = ui->Proc_stavka_lab->text();
    if (verification(credit_summa) && verification(credit_stavka) && verification_digit(credit_time)) {
        double summa = credit_summa.toDouble();
        int time = credit_time.toInt();
        double stavka = credit_stavka.toDouble();
        if (time <= 600 && stavka < 100 && time > 0 && stavka > 0 && summa >= 0) {
            double stavka_in_month = stavka / 12.0 / 100.0;
            if (ui->button_annu->isChecked()) {
                double annuitent = stavka_in_month * pow((stavka_in_month + 1), time) / (pow((stavka_in_month + 1), time) - 1) ;
                double pay_in_month = summa * annuitent;
                pay_in_month = floor(pay_in_month * 100 + 0.5) / 100;
                double dolg = pay_in_month * time;
                ui->result_pay->setText(QString::number(pay_in_month, 'f', 2));
                ui->result_proc->setText(QString::number(dolg - summa, 'f', 1) + "0");
                ui->result_pay_proc->setText(QString::number(dolg, 'f', 1) + "0");
                ui->label_error->setText("Бегом в банк!");
            }
            if (ui->button_diff->isChecked()) {
                double pay_in_month_osnov = summa / time;
                double proc_in_month = 0.0, sum_proc = 0.0, sum_dolg = 0.0;
                double pay_1 = 0.0;
                for (int i = 0; i < time; i++) {
                    proc_in_month = (((summa - (pay_in_month_osnov * i)) * stavka) / 12.0) / 100;
                    if (i == 0) pay_1 = pay_in_month_osnov + proc_in_month;
                    sum_proc += proc_in_month;
                }
                sum_dolg = summa + sum_proc;
                ui->result_pay->setText(QString::number(pay_1, 'f', 2) + " ... " + QString::number(pay_in_month_osnov + proc_in_month, 'f', 2));
                ui->result_proc->setText(QString::number(sum_proc, 'f', 2));
                ui->result_pay_proc->setText(QString::number(sum_dolg, 'f', 2));
                ui->label_error->setText("Бегом в банк!");
            }
        } else {
            ui->result_pay->setText("");
            ui->result_proc->setText("");
            ui->result_pay_proc->setText("");
            ui->label_error->setText("Срок кредита от 0 до 600 месяцев, ставка от 0.01 до 99.99!");
        }
    } else {
        ui->result_pay->setText("");
        ui->result_proc->setText("");
        ui->result_pay_proc->setText("");
        ui->label_error->setText("Некорректный ввод! Повтори, дружок!");
    }
}
