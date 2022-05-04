#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include <QMainWindow>
#include "graphics.h"
#include <QVector>

extern"C" {
#include "backend/s21_smart_calc.h"
#include "backend/s21_stack.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Graphics *window;

signals:
    void signal(QString, char*);

private slots:
    void digits_numbers();
    void on_pushButton_dot_clicked();
    void operations();
    void on_pushButton_plus_clicked();
    void on_pushButton_min_clicked();
    void on_pushButton_umn_clicked();
    void on_pushButton_del_clicked();
    void on_pushButton_pow_clicked();
    void on_pushButton_mod_clicked();
    void on_pushButton_res_clicked();
    void on_pushButton_ac_clicked();
    void on_pushButton_sin_clicked();
    void on_pushButton_cos_clicked();
    void on_pushButton_tan_clicked();
    void on_pushButton_asin_clicked();
    void on_pushButton_acos_clicked();
    void on_pushButton_atan_clicked();
    void on_pushButton_sqrt_clicked();
    void on_pushButton_ln_clicked();
    void on_pushButton_log_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_x_clicked();
    void on_pushButton_graph_clicked();
    char* converter(QString str);
    int check_number(QString new_label);
};

#endif // SRC_MAINWINDOW_H_
