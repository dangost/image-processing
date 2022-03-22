#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPixmap>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , imgEngine()
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

    this->imgEngine.RgbToGray(image);
    this->setImage(image);
}


void MainWindow::on_actionOpen_triggered()
{
    QString homeDirectory = qgetenv("HOME");
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open Image"),
                homeDirectory,
                tr("Image Files (*.png *.jpg *.bmp)")
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

    this->imgEngine.RgbToBinary(image);

    this->setImage(image);

}


void MainWindow::on_toWavesButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    this->imgEngine.RgbViaWaves(image);

    this->setImage(image);
}
