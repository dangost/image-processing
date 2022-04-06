#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class HistogramWindow;
}

class HistogramWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HistogramWindow(QWidget *parent = nullptr);
    ~HistogramWindow();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::HistogramWindow *ui;
};

#endif // HISTOGRAMWINDOW_H
