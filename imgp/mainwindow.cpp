#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "histogramwindow.h"

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

    drawA4Table(matrix, image.width(), image.height());
    drawA8Table(matrix, image.width(), image.height());

}


void MainWindow::on_toWavesButton_clicked()
{
    QImage image = this->ui->imageLabel->pixmap().toImage();

    double** matrix = this->imgCore.RgbViaWaves(image);
    this->fillTable(matrix, image.width(), image.height());

    this->setImage(image);

    for (int i = 0; i < image.width(); i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}


void MainWindow::drawA4Table(double **&matrix, int w, int h)
{
    double **result = new double*[w];

    for(int i = 0; i < w; i++)
        result[i] = new double[h];


    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            double sum = 0;
            sum += j - 1 > 0 && j - 1 < h ? matrix[i][j-1] : 0;
            sum += j + 1 > 0 && j + 1 < h ? matrix[i][j+1] : 0;
            sum += i - 1 > 0 && i - 1 < w ? matrix[i-1][j] : 0;
            sum += i + 1 > 0 && i + 1 < w ? matrix[i+1][j] : 0;

            result[i][j] = sum;
        }
    }

    this->ui->a4TableWidget->setRowCount(w);
    this->ui->a4TableWidget->setColumnCount(h);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            this->ui->a4TableWidget->setItem(i, j, new QTableWidgetItem(QString::number(result[i][j])));
        }

        delete[] result[i];
    }

    delete[] result;
}


void MainWindow::drawA8Table(double **& matrix, int w, int h)
{
    double **result = new double*[w];

    for(int i = 0; i < w; i++)
        result[i] = new double[h];


    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            double sum = 0;
            sum += j - 1 > 0 && j - 1 < h ? matrix[i][j-1] : 0;
            sum += j + 1 > 0 && j + 1 < h ? matrix[i][j+1] : 0;
            sum += i - 1 > 0 && i - 1 < w ? matrix[i-1][j] : 0;
            sum += i + 1 > 0 && i + 1 < w ? matrix[i+1][j] : 0;

            sum += j - 1 > 0 && j - 1 && i - 1 > 0 && i - 1 < w  < h ? matrix[i-1][j-1] : 0;
            sum += j - 1 > 0 && j - 1 < h && i + 1 > 0 && i + 1 < w ? matrix[i+1][j-1] : 0;

            sum += j + 1 > 0 && j + 1 < h && i - 1 > 0 && i - 1 < w  ? matrix[i-1][j+1] : 0;
            sum += j + 1 > 0 && j + 1 < h && i + 1 > 0 && i + 1 < w ? matrix[i+1][j+1] : 0;

            result[i][j] = sum;
        }
    }

    this->ui->a8TableWidget->setRowCount(w);
    this->ui->a8TableWidget->setColumnCount(h);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            this->ui->a8TableWidget->setItem(i, j, new QTableWidgetItem(QString::number(result[i][j])));
        }
        delete[] matrix[i];
        delete[] result[i];
    }
    delete[] matrix;
    delete[] result;
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
    this->fillTable(matrix, image.width(), image.height());
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

    this->fillTable(matrix, image.width(), image.height());

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
    this->fillTable(matrix, image.width(), image.height());

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
    this->fillTable(matrix, image.width(), image.height());

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
    this->fillTable(matrix, image.width(), image.height());

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
    this->fillTable(matrix, image.width(), image.height());

    this->setImage(image);

    for (int i = 0; i < image.width(); i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}


void MainWindow::on_outputTableWidget_cellChanged(int row, int column)
{
    //this->ui->outputTableWidget->setItem(i, j, new QTableWidgetItem(QString::number(matrix[i][j])));
    int value = this->ui->outputTableWidget->item(row, column)->text().toInt();
    QImage image = this->ui->imageLabel->pixmap().toImage();
    QColor color(image.pixelColor(row, column));
    int red = color.red();
    int blue = color.blue();
    int green = color.green();

    switch(this->lastColor){
    case 1:
        red = value;
        break;
    case 2:
        green = value;
        break;
    case 3:
        blue = value;
        break;
    }

    image.setPixel(row,column, qRgb(red, green, blue));

    this->setImage(image);


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

