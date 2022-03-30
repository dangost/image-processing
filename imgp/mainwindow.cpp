#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPixmap>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , imgCore()
{
    ui->setupUi(this);
}

void MainWindow::actionOpen()
{
    qDebug() << "action Open!";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillTable(double **& matrix, int w, int h)
{
    this->ui->outputTableWidget->setRowCount(w);
    this->ui->outputTableWidget->setColumnCount(h);

    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
        {
            this->ui->outputTableWidget->setItem(i, j, new QTableWidgetItem(QString::number(matrix[i][j])));
        }
}

void MainWindow::setImage(QImage &image)
{
    QPixmap imagePix = QPixmap::fromImage(image);
    this->ui->imageLabel->setPixmap(
                imagePix.scaled(
                    this->ui->imageLabel->width(),
                    this->ui->imageLabel->height(),
                    Qt::KeepAspectRatio));
}


void MainWindow::on_ToGrayButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double **matrix = this->imgCore.RgbToGray(image);
    this->fillTable(matrix, image.width(), image.height());
    this->setImage(image);
}


void MainWindow::on_actionOpen_triggered()
{
    QString homeDirectory = qgetenv("HOME");
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open Image"),
                homeDirectory,
                tr("Image Files (*.png *.jpg *.bmp *.jpeg)")
                );

    QPixmap openedImage(fileName);

    this->ui->imageLabel->setPixmap(
                openedImage.scaled(
                    this->ui->imageLabel->width(),
                    this->ui->imageLabel->height(),
                    Qt::KeepAspectRatio));
}


void MainWindow::on_actionSave_triggered()
{
    QString homeDirectory = qgetenv("HOME");
    QString path = QFileDialog::getSaveFileName(this, tr("Choose folder to save"), homeDirectory);

    this->ui->imageLabel->pixmap().toImage().save(path);
}


void MainWindow::on_actionExit_triggered()
{
    exit(0);
}


void MainWindow::on_toBinaryButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double** matrix = this->imgCore.RgbToBinary(image);
    this->fillTable(matrix, image.width(), image.height());

    this->setImage(image);
}


void MainWindow::on_toWavesButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double** matrix = this->imgCore.RgbViaWaves(image);
    this->fillTable(matrix, image.width(), image.height());

    this->setImage(image);
}
