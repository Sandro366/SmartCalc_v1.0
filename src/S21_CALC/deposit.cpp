#include "deposit.h"
#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deposit)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    index_vyp = 0;
    index_pop = 0;
    index_snyat = 0;
}

Deposit::~Deposit() {
    delete ui;
}

void Deposit::on_button_OK_clicked() {
    QString vklad_summa = ui->Summa_vklad->text();
    QString vklad_time = ui->Time_vklad->text();
    QString vklad_procent = ui->Proc_stavka->text();
    QString vklad_nalog = ui->Nalog_stavka->text();
    QString vklad_popoln = ui->Summa_popoln->text();
    QString vklad_snyat = ui->Summa_snyat->text();
    if (verification(vklad_summa) && verification(vklad_procent) && verification(vklad_nalog) &&
            verification_digit(vklad_time) && verification(vklad_popoln) && verification(vklad_snyat)) {
        double summa = vklad_summa.toDouble();
        int time = vklad_time.toInt();
        double stavka = vklad_procent.toDouble();
        double tax_rate = vklad_nalog.toDouble();
        double summa_popoln = vklad_popoln.toDouble();
        double summa_snyat = vklad_snyat.toDouble();
        double summa_proc = 0.0, NDFL = 0.0, NDFL_year = 0.0;
        if (time <= 600 && stavka < 100 && time > 0 && stavka >= 0 && summa >= 0 &&
                summa_popoln >= 0 && summa_snyat >= 0 && tax_rate >= 0 && tax_rate < 100) {
            double limit_nalog = tax_rate * 10000;
            QDate date_now = ui->dateEdit->date();
            QDate date_end = date_now.addMonths(time);
            QDate date_popoln = date_now_add(date_now, index_pop);
            QDate date_snyat = date_now_add(date_now, index_snyat);
            QDate date_nalog;
            QDate date_vyplat = date_vyplat_index(date_now, index_vyp);
            int year_now = date_now.year();
            date_nalog = date_vyplat;
            if (index_vyp == 0) {
                date_nalog.setDate(date_now.year(), 12, 31);
            } else if (index_vyp == 6) {
                date_nalog = date_now;
            } else {
                while ((int)date_nalog.year() == year_now) {
                    QDate date_nalog_temp = date_vyplat_index(date_nalog, index_vyp);
                    if ((int)date_nalog_temp.year() == year_now) date_nalog = date_nalog_temp;
                    else break;
                }
            }
            if (ui->Kapital->isChecked() && index_vyp != 6) {
                double summa_kapital = 0.0;
                while (date_now != date_end) {
                    date_now = date_now.addDays(1);
                    double days_year = date_now.daysInYear();
                    double summa_kapital_temp = summa * (1 + (stavka/(100.0 * days_year))) - summa;
                    summa_kapital = summa_kapital + summa_kapital_temp;
                    NDFL_year += summa_kapital_temp;
                    if (index_snyat != 0 && date_now == date_snyat) {
                        summa -=  summa_snyat;
                        if (summa < 0) {
                            summa += summa_snyat;
                        }
                        date_snyat = date_now_add(date_now, index_snyat);
                    }
                    if (date_now == date_vyplat) {
                        summa_proc += summa_kapital;
                        summa += summa_kapital;
                        summa_kapital = 0;
                        date_vyplat = date_vyplat_index(date_now, index_vyp);
                    }
                    if (date_now == date_nalog) {
                        if (NDFL_year > limit_nalog && date_nalog.year() != 2022) NDFL = NDFL + ((NDFL_year - limit_nalog) * 0.13);
                        NDFL_year = 0;
                        if (index_vyp == 1) {
                            date_nalog = date_nalog.addDays(364);
                            QDate temp_date = date_nalog.addDays(7);
                            if (temp_date.year() == date_nalog.year()) {
                                date_nalog.setDate(temp_date.year(), temp_date.month(), temp_date.day());
                            }
                        } else date_nalog = date_nalog.addYears(1);
                    }
                    if (index_pop != 0 && date_now == date_popoln) {
                        summa += summa_popoln;
                        date_popoln = date_now_add(date_now, index_pop);
                    }
                    if (date_now == date_end) {
                        summa_proc += summa_kapital;
                        summa += summa_kapital;
                        if (NDFL_year > limit_nalog) NDFL = NDFL + ((NDFL_year - limit_nalog) * 0.13);
                    }
                }
            } else {
                while (date_now != date_end) {
                    date_now = date_now.addDays(1);
                    double days_year = date_now.daysInYear();
                    double profit = (summa * stavka) / (days_year * 100.0);
                    summa_proc += profit;
                    NDFL_year += profit;
                    if (date_now == date_nalog) {
                        if (NDFL_year > limit_nalog && date_nalog.year() != 2022) NDFL = NDFL + ((NDFL_year - limit_nalog) * 0.13);
                        NDFL_year = 0;
                        if (index_vyp == 1) {
                            date_nalog = date_nalog.addDays(364);
                            QDate temp_date = date_nalog.addDays(7);
                            if (temp_date.year() == date_nalog.year()) {
                                date_nalog.setDate(temp_date.year(), temp_date.month(), temp_date.day());
                            }
                        } else date_nalog = date_nalog.addYears(1);
                    }
                    if (date_now == date_end && NDFL_year > limit_nalog) NDFL = NDFL + ((NDFL_year - limit_nalog) * 0.13);
                    if (index_pop != 0 && date_now == date_popoln) {
                        summa += summa_popoln;
                        date_popoln = date_now_add(date_now, index_pop);
                    }
                    if (index_snyat != 0 && date_now == date_snyat) {
                        summa -=  summa_snyat;
                        if (summa < 0) {
                            summa = 0;
                            break;
                        }
                        date_snyat = date_now_add(date_now, index_snyat);
                    }
                }
                if (index_vyp == 6 && ui->Kapital->isChecked()) summa = summa + summa_proc;
            }
            ui->result_proc->setText(QString::number(summa_proc, 'f', 2));
            ui->result_nalog->setText(QString::number(NDFL, 'f', 2));
            ui->result_summa_vklad->setText(QString::number(summa, 'f', 2));
            ui->label_error->setText("Бегом в банк!");
        } else {
            ui->result_proc->setText("");
            ui->result_nalog->setText("");
            ui->result_summa_vklad->setText("");
            ui->label_error->setText("Неверно вводишь цифровые данные!");
        }
    } else {
        ui->result_proc->setText("");
        ui->result_nalog->setText("");
        ui->result_summa_vklad->setText("");
        ui->label_error->setText("Некорректный ввод, лишние символы (буквы, знаки)! Повтори, дружок!");
    }
}

void Deposit::on_Box_vyplaty_activated(int index) {
    index_vyp = index;
}

void Deposit::on_Box_popoln_activated(int index) {
    index_pop = index;
    if (index == 0) {
        ui->Summa_popoln->setEnabled(false);
        ui->Summa_popoln->setStyleSheet("QLineEdit { background: rgb(200, 211, 201); border: 2px solid black;}");
    } else {
        ui->Summa_popoln->setEnabled(true);
        ui->Summa_popoln->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); border: 2px solid black;}");
    }
}

void Deposit::on_Box_snyat_activated(int index) {
    index_snyat = index;
    if (index == 0) {
        ui->Summa_snyat->setEnabled(false);
        ui->Summa_snyat->setStyleSheet("QLineEdit { background: rgb(200, 211, 201); border: 2px solid black;}");
    } else {
        ui->Summa_snyat->setEnabled(true);
        ui->Summa_snyat->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); border: 2px solid black;}");
    }
}

QDate date_now_add(QDate date_now, int index) {
    QDate result;
    if (index == 1) {result = date_now.addMonths(1);}
    if (index == 2) {result = date_now.addMonths(2);}
    if (index == 3) {result = date_now.addMonths(3);}
    if (index == 4) {result = date_now.addMonths(6);}
    if (index == 5) {result = date_now.addYears(1);}
    return result;
}

QDate date_vyplat_index(QDate date_now, int index) {
    QDate result;
    if (index == 0) {result = date_now.addDays(1);}
    if (index == 1) {result = date_now.addDays(7);}
    if (index == 2) {result = date_now.addMonths(1);}
    if (index == 3) {result = date_now.addMonths(3);}
    if (index == 4) {result = date_now.addMonths(6);}
    if (index == 5) {result = date_now.addYears(1);}
    if (index == 6) {result = date_now.addMonths(1);}
    return result;
}

void Deposit::on_button_back_clicked()
{
    emit close_deposit();
    close();
}
