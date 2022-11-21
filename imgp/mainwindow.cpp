#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "histogramwindow.h"
#include "secondwindow.h"

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
    this->setImage(image);
    this->setMainTable(matrix, image.width(), image.height());
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

void MainWindow::on_actionSecondSemester_triggered()
{
    exit(0);
}


void MainWindow::on_toBinaryButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double** matrix = this->imgCore.RgbToBinary(image);

    this->setImage(image);

}


void MainWindow::on_toWavesButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double** matrix = this->imgCore.RgbViaWaves(image);

    this->setImage(image);

    for (int i = 0; i < image.width(); i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

void MainWindow::on_histogramButton_clicked()
{
    HistogramWindow *histogramWindow = new HistogramWindow();
    histogramWindow->show();
}


void MainWindow::on_s8Button_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double **matrix = this->imgCore.S8Binarisation(image);
    this->setImage(image);

    for (int i = 0; i < image.width(); i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}


void MainWindow::on_globalBinaruButton_clicked()
{
    int value = this->ui->globalSlider->value();
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double** matrix = this->imgCore.GlobalBinarisation(image, value);

    this->setImage(image);

    for (int i = 0; i < image.width(); i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;

}


void MainWindow::on_redButton_clicked()
{
    this->lastColor = 1;
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double **matrix = this->imgCore.RedMatrix(image);

    for (int i = 0; i < image.width(); i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}


void MainWindow::on_greenButton_clicked()
{
    this->lastColor = 2;
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double **matrix = this->imgCore.GreenMatrix(image);

    for (int i = 0; i < image.width(); i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}


void MainWindow::on_blueButton_clicked()
{
    this->lastColor = 3;
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double **matrix = this->imgCore.BlueMatrix(image);

    for (int i = 0; i < image.width(); i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

void MainWindow::on_minMaxButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double **matrix = this->imgCore.MinMaxGrayImage(image);

    this->setImage(image);

    for (int i = 0; i < image.width(); i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

void MainWindow::on_filterButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double** matrix = this->imgCore.Filter(image);

    this->setImage(image);

    for (int i = 0; i < image.width(); i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}


void MainWindow::on_globalSlider_sliderMoved(int position)
{
    this->ui->sliderValueLabel->setText(QString::number(this->ui->globalSlider->value()));
}


void MainWindow::on_actionSave_2_triggered()
{
    QString homeDirectory = qgetenv("HOME");
    QString path = QFileDialog::getSaveFileName(this, tr("Choose folder to save"), homeDirectory);

    this->ui->imageLabel->pixmap().toImage().save(path);
}


void MainWindow::setMainTable(double** image, int width, int height)
{
    this->ui->mainTableWidget = new QTableWidget(this);
    this->ui->mainTableWidget->setRowCount(height);
    this->ui->mainTableWidget->setColumnCount(width);

    for (int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            auto item = new QTableWidgetItem();
            item->setText(QString::number((int)image[x][y]));

            this->ui->mainTableWidget->setItem(x, y, item);
        }
    }
}


void MainWindow::on_pushButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    int mask[8];

    mask[0] = this->ui->mastTableWidget->item(0, 0)->text().toInt();
    mask[1] = this->ui->mastTableWidget->item(1, 0)->text().toInt();
    mask[2] = this->ui->mastTableWidget->item(2, 0)->text().toInt();

    mask[3] = this->ui->mastTableWidget->item(0, 1)->text().toInt();
    mask[4] = this->ui->mastTableWidget->item(1, 1)->text().toInt();

    mask[5] = this->ui->mastTableWidget->item(0, 2)->text().toInt();
    mask[6] = this->ui->mastTableWidget->item(1, 2)->text().toInt();
    mask[7] = this->ui->mastTableWidget->item(2, 2)->text().toInt();

    double** matrix = this->imgCore.Unlocking(image, mask);

    this->setImage(image);

    for (int i = 0; i < image.width(); i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}


void MainWindow::on_pushButton_2_clicked()
{

}


void MainWindow::on_actionSecond_Semester_triggered()
{
    SecondWindow *window = new SecondWindow(this);
    window->show();

}

