#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imgprocessing.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void actionOpen();

private slots:
    void on_ToGrayButton_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_toBinaryButton_clicked();

    void on_toWavesButton_clicked();

    void on_histogramButton_clicked();

    void on_s8Button_clicked();

    void on_globalBinaruButton_clicked();

private:
    Ui::MainWindow *ui;

    ImageProcessingCore imgCore;

    void setImage(QImage &);

    void fillTable(double **& matrix, int w, int h);

    void drawA4Table(double **& matrix, int w, int h);
    void drawA8Table(double **& matrix, int w, int h);
};
#endif // MAINWINDOW_H
