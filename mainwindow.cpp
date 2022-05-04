#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDir>
#include <QStringList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    window = new Graphics(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_unar, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_right, SIGNAL(clicked()), this, SLOT(operations()));
    connect(this, &MainWindow::signal, window, &Graphics::slot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();
    QString new_label;

    if (button->text() == '0') {
        if (ui->result_show->text().endsWith("0") && ui->result_show->text().length() == 1) {
            new_label = button->text();
        } else if(!(ui->result_show->text().endsWith("/"))) {
            new_label = ui->result_show->text() + button->text();
        } else {
            new_label = ui->result_show->text();
        }
    } else if (ui->result_show->text().endsWith("0") && ui->result_show->text().length() == 1) {
       new_label = button->text();
    } else if (ui->result_show->text().endsWith("n.")) {
        new_label = button->text();
    } else {
       if (!(ui->result_show->text().endsWith("x"))) {
           new_label = ui->result_show->text() + button->text();
       } else {
           new_label = ui->result_show->text();
       }
    }

    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (!(ui->result_show->text().endsWith(".")))
        ui->result_show->setText(ui->result_show->text() + ".");
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton *)sender();
    QString new_label;

    if (ui->result_show->text().endsWith('0') && ui->result_show->text().length() == 0) {
        ui->result_show->setText("");
    }
    if (button->text() == "+/-") {
        int len = ui->result_show->text().length();
        printf("%d\n", len);
        if (!(ui->result_show->text().startsWith('0')) && !(ui->result_show->text().length() == 0)) { // доделать чтобы если 0 стоит то нельзя юзать +-
                if (ui->result_show->text().startsWith("-")) {
                    new_label = ui->result_show->text();
                    new_label.remove(0, 1);
                    ui->result_show->setText(new_label);
                } else {
                    ui->result_show->setText( "-" + ui->result_show->text());
                }
        }
    } else if (button->text() == "(") {
        if (ui->result_show->text().endsWith("0") && ui->result_show->text().length() == 1) {
            new_label = button->text();
            ui->result_show->setText(new_label);
        } else {
            if (!ui->result_show->text().endsWith(')'))
                ui->result_show->setText(ui->result_show->text() + "(");
        }
    } else if (button->text() == ")") {
        if (!ui->result_show->text().endsWith('('))
        ui->result_show->setText(ui->result_show->text() + ")");
    }

}


void MainWindow::on_pushButton_plus_clicked()
{
    if (!(ui->result_show->text().endsWith('+')))
        ui->result_show->setText(ui->result_show->text() + "+");
}


void MainWindow::on_pushButton_min_clicked()
{
    if (!(ui->result_show->text().endsWith('-')) && (!(ui->result_show->text().startsWith("0")) || ui->result_show->text().length() > 1))
        ui->result_show->setText(ui->result_show->text() + "-");
}


void MainWindow::on_pushButton_umn_clicked()
{
    if (!(ui->result_show->text().endsWith('*')) && (!(ui->result_show->text().startsWith("0")) || ui->result_show->text().length() > 1))
        ui->result_show->setText(ui->result_show->text() + "*");
}


void MainWindow::on_pushButton_del_clicked()
{
    if (!(ui->result_show->text().endsWith("/")) && (!(ui->result_show->text().startsWith("0")) || ui->result_show->text().length() > 1))
        ui->result_show->setText(ui->result_show->text() + "/");
}


void MainWindow::on_pushButton_pow_clicked()
{
    if (!(ui->result_show->text().endsWith('^')) && (!(ui->result_show->text().startsWith("0")) || ui->result_show->text().length() > 1))
        ui->result_show->setText(ui->result_show->text() + "^");
}


void MainWindow::on_pushButton_mod_clicked()
{
    if (!(ui->result_show->text().endsWith("mod")) && (!(ui->result_show->text().startsWith("0")) || ui->result_show->text().length() > 1))
        ui->result_show->setText(ui->result_show->text() + "mod");
}


void MainWindow::on_pushButton_res_clicked()
{
        QString new_label = ui->result_show->text();
        char* str = converter(new_label);
        double x = 0.0;
        if (check(str) == 0) {
            ui->result_show->setText("Error expression! Try again.");
        } else if (new_label.contains("x")) {
            on_pushButton_graph_clicked();
        } else {
            double result = readstr(str, x);
            QString numberResult = QString::number(result, 'g', 15);
            ui->result_show->setText(numberResult);
        }
        delete(str);
}


void MainWindow::on_pushButton_ac_clicked()
{
    ui->result_show->setText("0");
}


void MainWindow::on_pushButton_sin_clicked()
{
    if (ui->result_show->text().startsWith("0"))
        ui->result_show->setText("");
    ui->result_show->setText(ui->result_show->text() + "sin(");
}


void MainWindow::on_pushButton_cos_clicked()
{
    if (ui->result_show->text().startsWith("0"))
        ui->result_show->setText("");
    ui->result_show->setText(ui->result_show->text() + "cos(");
}


void MainWindow::on_pushButton_tan_clicked()
{
    if (ui->result_show->text().startsWith("0"))
        ui->result_show->setText("");
    ui->result_show->setText(ui->result_show->text() + "tan(");
}


void MainWindow::on_pushButton_asin_clicked()
{
    if (ui->result_show->text().startsWith("0"))
        ui->result_show->setText("");
    ui->result_show->setText(ui->result_show->text() + "asin(");
}


void MainWindow::on_pushButton_acos_clicked()
{
    if (ui->result_show->text().startsWith("0"))
        ui->result_show->setText("");
    ui->result_show->setText(ui->result_show->text() + "acos(");
}


void MainWindow::on_pushButton_atan_clicked()
{
    if (ui->result_show->text().startsWith("0"))
        ui->result_show->setText("");
    ui->result_show->setText(ui->result_show->text() + "atan(");
}


void MainWindow::on_pushButton_sqrt_clicked()
{
    if (ui->result_show->text().startsWith("0"))
        ui->result_show->setText("");
    ui->result_show->setText(ui->result_show->text() + "sqrt(");
}


void MainWindow::on_pushButton_ln_clicked()
{
    if (ui->result_show->text().startsWith("0"))
        ui->result_show->setText("");
    ui->result_show->setText(ui->result_show->text() + "ln(");
}


void MainWindow::on_pushButton_log_clicked()
{
    if (ui->result_show->text().startsWith("0"))
        ui->result_show->setText("");
    ui->result_show->setText(ui->result_show->text() + "log(");
}


void MainWindow::on_pushButton_delete_clicked()
{
    QString new_label;
    new_label = ui->result_show->text();
    if (new_label.length() == 1) {
        ui->result_show->setText("0");
    } else {
        new_label.remove(new_label.length()-1, 1);
        ui->result_show->setText(new_label);
    }
}


void MainWindow::on_pushButton_x_clicked()
{
    if (!(ui->result_show->text().endsWith("x")) && (check_number(ui->result_show->text()) || ui->result_show->text().endsWith("0"))) {
        if (ui->result_show->text().endsWith("0") && ui->result_show->text().length() == 1) {
             ui->result_show->setText("x");
        } else {
            ui->result_show->setText(ui->result_show->text() + "x");
        }
    }
}


void MainWindow::on_pushButton_graph_clicked()
{
    char* label = converter(ui->result_show->text());
    window->show();
    emit signal(ui->result_show->text(), label);
}

char* MainWindow::converter(QString new_label) {
    int idx, cnt = 0;
    while (cnt != 10) {
        if (new_label.contains("asin")) { // i
            idx = new_label.indexOf("asin");
            new_label.remove(idx+3, 1);
            new_label.remove(idx, 2);
        } else if (new_label.contains("acos")) { // o
            idx = new_label.indexOf("acos");
            new_label.remove(idx+3, 1);
            new_label.remove(idx, 2);
        } else if (new_label.contains("atan")) { // a
            idx = new_label.indexOf("atan");
            new_label.remove(idx+1, 3);
        } else if (new_label.contains("mod")) { // m
            idx = new_label.indexOf("mod");
            new_label.remove(idx+1, 2);
        } else if (new_label.contains("sin")) { // s
            idx = new_label.indexOf("sin");
            new_label.remove(idx+1, 2);
        } else if (new_label.contains("cos")) { // c
            idx = new_label.indexOf("cos");
            new_label.remove(idx+1, 2);
        } else if (new_label.contains("tan")) { // t
            idx = new_label.indexOf("tan");
            new_label.remove(idx+1, 2);
        } else if (new_label.contains("sqrt")) { // q
            idx = new_label.indexOf("sqrt");
            new_label.remove(idx+2, 2);
            new_label.remove(idx, 1);
        } else if (new_label.contains("ln")) { // n
            idx = new_label.indexOf("ln");
            new_label.remove(idx, 1);
        } else if (new_label.contains("log")) { // l
            idx = new_label.indexOf("log");
            new_label.remove(idx+1, 2);
        }
        cnt++;
    }
    char* str = new char(new_label.length());
    QByteArray barr = new_label.toLatin1();
    strlcpy(str, barr, new_label.length() + 1);
    return str;
}

int MainWindow::check_number(QString new_label) {
    int res = 1;
    if (new_label.endsWith("0") || new_label.endsWith("1") || new_label.endsWith("2") || new_label.endsWith("3") || new_label.endsWith("4")
    || new_label.endsWith("5")|| new_label.endsWith("6") || new_label.endsWith("7") || new_label.endsWith("8") || new_label.endsWith("9")) {
        res = 0;
    }
    return res;
}
