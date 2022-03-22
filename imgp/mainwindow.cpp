#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPixmap>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

    for(int x = 0; x < image.width(); x++)
    {
        for(int y = 0; y < image.height(); y++)
        {
            QColor rgb = image.pixelColor(x, y);
            int gray = (rgb.red() + rgb.blue() + rgb.green()) / 3;

            image.setPixel(x, y, QColor(gray, gray, gray).rgb());
        }
    }

    this->setImage(image);
}


void MainWindow::on_actionOpen_triggered()
{
    // QString homeDirectory = qgetenv("HOME");
//    QString fileName = QFileDialog::getOpenFileName(
//                this, tr("Open Image"),
//                homeDirectory,
//                tr("Image Files (*.png *.jpg *.bmp)")
//                );
    QString fileName = "/Users/gost/Documents/Pictures/me.jpg";
    QPixmap openedImage(fileName);

    this->ui->imageLabel->setPixmap(
                openedImage.scaled(
                    this->ui->imageLabel->width(),
                    this->ui->imageLabel->height(),
                    Qt::KeepAspectRatio));



    std::cout << fileName.toStdString();
}


void MainWindow::on_actionSave_triggered()
{

}


void MainWindow::on_actionExit_triggered()
{
    exit(0);
}


void MainWindow::on_toBinaryButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    for(int x = 0; x < image.width(); x++)
    {
        for(int y = 0; y < image.height(); y++)
        {
            QColor rgb = image.pixelColor(x, y);
            int gray = (rgb.red() + rgb.blue() + rgb.green()) / 3;

            int color = gray > 128 ? 255 : 0;

            image.setPixel(x, y, QColor(color, color, color).rgb());
        }
    }

    this->setImage(image);

}


void MainWindow::on_toWavesButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    const int w = image.width();
    const int h = image.height();

    double **matrix = new double*[w];

    for(int i = 0; i < image.width(); i++)
        matrix[i] = new double[h];

    for(int i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
        {
            QColor rgb = image.pixelColor(i, j);
            int gray = (rgb.red() + rgb.blue() + rgb.green()) / 3;
            matrix[i][j] = gray > 128 ? 0 : 1;
        }

    double min = 0;
    double max = 1;
    this->waveMatrix(matrix, w , h, max, min);

    double relativeValue = max - min;
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            double temp = matrix[i][j];
            if (temp >= 0.1)
            {
                ;
            }
            int color = 255 - (int)((temp * 255) / relativeValue);
            image.setPixel(i, j, QColor(color, color, color).rgb());
        }
    }

    qDebug() << "Min: " << min << " Max: " << max;

    for (int i = 0; i < w; i++)  // clear ram
        delete[] matrix[i];
    delete[] matrix;

    this->setImage(image);
}

void MainWindow::waveMatrix(double **&matrix, int w, int h, double &max, double &min)
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (matrix[i][j] == 1)
            {
                for (int x = -3; x <= 3; x++)
                {
                    for (int y = -2; y <= 3; y++)
                    {
                        double increment;
                        if (!(x > -3 && x < 3 && y > -3 && y < 3))
                        {
                            increment = 0.1;
                        }
                        else if (!(x > -2 && x < 2 && y > -2 && y < 2))
                        {
                            increment = 0.3;
                        }
                        else if (!(x > -1 && x < 1 && y > -1 && y < 1))
                        {
                            increment = 0.6;
                        }
                        else
                            continue;

                        if ((i+x >=0 && i+x < w) && (j+y >= 0 && j+y < h))
                        {
                            matrix[i+x][j+y] += increment;

                            double value = matrix[i+x][j+y];
                            if (value > max)
                                max = value;
                            else if (value < min)
                                min = value;
                        }
                    }
                }
            }
        }
    }
}

