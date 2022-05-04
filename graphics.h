#ifndef SRC_GRAPHICS_H_
#define SRC_GRAPHICS_H_

#include <QDialog>

extern"C" {
#include "backend/s21_smart_calc.h"
#include "backend/s21_stack.h"
}

namespace Ui {
class Graphics;
}

class Graphics : public QDialog
{
    Q_OBJECT

public:
    explicit Graphics(QWidget *parent = nullptr);
    ~Graphics();

private slots:

    void on_pushButton_draw_clicked();

private:
    Ui::Graphics *ui;
   char* label;

public slots:
    void slot(QString text, char* lab);
};

#endif // SRC_GRAPHICS_H_
