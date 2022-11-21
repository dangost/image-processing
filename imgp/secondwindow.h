#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include "imgprocessing.h"
#include "lab01matrix.h"
#include "lab02core.h"

#include <QLabel>
#include <QMainWindow>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void set_image(QLabel *label, QImage image);

    void setTables(QTableWidget *table1, QTableWidget *table2, QTableWidget *table3, QImage image,
                   QLabel *energy, QLabel *entropy, QLabel *contrast, QLabel *homo);
    void on_compareButton_clicked();

    void on_image2open_clicked();

    void on_thinButton_clicked();

private:
    Ui::SecondWindow *ui;
     ImageProcessingCore imgCore;
     Lab01Matrix lab01;
     Lab02Core lab02;
};

#endif // SECONDWINDOW_H
