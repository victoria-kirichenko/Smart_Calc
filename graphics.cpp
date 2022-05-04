#include "graphics.h"
#include "ui_graphics.h"

Graphics::Graphics(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graphics)
{
    ui->setupUi(this);
}

Graphics::~Graphics()
{
    delete ui;
}

void Graphics::on_pushButton_draw_clicked()
{
    ui->widget->clearGraphs();
    char* str = label;
    double x_max = ui->x_max->text().toDouble();
    double x_min = ui->x_min->text().toDouble();
    double d_y = ui->d_y->text().toDouble();
    double e_y = ui->e_y->text().toDouble();

    QVector<double> x, y;
    double h = 0.1, X;

    ui->widget->xAxis->setRange(-1 * d_y, d_y);
    ui->widget->yAxis->setRange(-1 * e_y, e_y);

    for (X = x_min; X <= x_max; X += h) {
        x.push_back(X);
        y.push_back(readstr(str, X));
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();

    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    delete(str);
}

void Graphics::slot(QString text, char* lab)
{
    label = lab;;
    ui->func->setText(text);
}

