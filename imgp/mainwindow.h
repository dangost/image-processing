#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    void setImage(QImage &);

    void waveMatrix(double **&, int, int, double&, double&);
};
#endif // MAINWINDOW_H
