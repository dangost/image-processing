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
    void on_actionSecondSemester_triggered();

    void on_toBinaryButton_clicked();

    void on_toWavesButton_clicked();

    void on_histogramButton_clicked();

    void on_s8Button_clicked();

    void on_globalBinaruButton_clicked();

    void on_redButton_clicked();

    void on_greenButton_clicked();

    void on_blueButton_clicked();

    void on_minMaxButton_clicked();

    void on_globalSlider_sliderMoved(int position);

    void on_actionSave_2_triggered();

    void on_filterButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionSecond_Semester_triggered();

private:
    Ui::MainWindow *ui;

    void setMainTable(double** image, int width, int height);

    ImageProcessingCore imgCore;

    void setImage(QImage &);

    int lastColor;
};
#endif // MAINWINDOW_H
