#include "histogramwindow.h"
#include "ui_histogramwindow.h"

HistogramWindow::HistogramWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistogramWindow)
{
    ui->setupUi(this);

    QPixmap image("/Users/gost/pets/image-processing/imgp/3.jpg");

    this->ui->pixmapLabel->setPixmap(image
            .scaled(
                this->ui->pixmapLabel->width(),
                this->ui->pixmapLabel->height(),
                Qt::KeepAspectRatio));

    QPixmap image1("/Users/gost/pets/image-processing/imgp/4.jpg");

    this->ui->gisLlabel->setPixmap(image1
            .scaled(
                this->ui->pixmapLabel->width(),
                this->ui->pixmapLabel->height(),
                Qt::KeepAspectRatio));
}

HistogramWindow::~HistogramWindow()
{
    delete ui;
}

void HistogramWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    this->close();
}

