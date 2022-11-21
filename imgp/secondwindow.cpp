#include "secondwindow.h"
#include "ui_secondwindow.h"

#include <QFileDialog>
#include <QByteArrayView>

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow),
    imgCore(),
    lab01(),
    lab02()
{

    ui->setupUi(this);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::set_image(QLabel *label, QImage image)
{
    auto pixmap = QPixmap::fromImage(image);
    label->setPixmap(
                pixmap.scaled(
                    label->width(),
                    label->height(),
                    Qt::KeepAspectRatio));
}

void SecondWindow::setTables(QTableWidget *table1, QTableWidget *table2, QTableWidget *table3, QImage image,
                             QLabel *energy, QLabel *entropy, QLabel *contrast, QLabel *homo)
{
    double** baseMatrix = this->lab01.GetBaseMatrix(image);

    table1->setRowCount(image.height());
    table1->setColumnCount(image.width());

    for (int x = 0; x < image.width(); x++)
    {
        for(int y = 0; y < image.height(); y++)
        {
            auto item = new QTableWidgetItem();
            QString value = QString::number((int)baseMatrix[x][y]);
            item->setText(value);

            table1->setItem(y, x, item);
        }
    }

    double** mastrixSmezh = this->lab01.Smezhnost(baseMatrix, image.width(), image.height());

    for (int i = 0; i < image.width(); i++)
    {
        delete[] baseMatrix[i];
    }

    delete[] baseMatrix;
    table2->setRowCount(8);
    table2->setColumnCount(8);

    for (int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            auto item = new QTableWidgetItem();
            item->setText(QString::number((int)mastrixSmezh[x][y]));

            table2->setItem(y, x, item);
        }
    }

    double** normalizeSmezh = this->lab01.NormalizedMatrix(mastrixSmezh);
    for (int i = 0; i < 8; i++)
    {
        delete[] mastrixSmezh[i];
    }

    delete[] mastrixSmezh;

    table3->setRowCount(8);
    table3->setColumnCount(8);

    for (int x = 0; x < 8; x++)
    {
        for(int y = 0; y < 8; y++)
        {
            auto item = new QTableWidgetItem();
            item->setText(QString::number(normalizeSmezh[x][y]));

            table3->setItem(y, x, item);
        }
    }

    double m_enetry = this->lab01.enegry(normalizeSmezh, 8, 8);
    double m_entropy = this->lab01.entropy(normalizeSmezh, 8, 8);
    double m_contrast = this->lab01.contrast(normalizeSmezh, 8, 8);
    double m_homo = this->lab01.homo(normalizeSmezh, 8, 8);

    energy->setText(QString::number(m_enetry));
    entropy->setText(QString::number(m_entropy));
    contrast->setText(QString::number(m_contrast));
    homo->setText(QString::number(m_homo));

    for (int i = 0; i < 8; i++)
    {
        delete[] normalizeSmezh[i];
    }

    delete[] normalizeSmezh;
}

void SecondWindow::on_pushButton_4_clicked()
{
    QString homeDirectory = QString("/Users/gost/Documents");
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open Image"),
                homeDirectory,
                tr("Image Files (*.png *.jpg *.bmp *.jpeg)")
                );

    QPixmap openedImage(fileName);
    QImage image = openedImage.toImage();
    this->set_image(this->ui->image4label, image);
    image = this->ui->image4label->pixmap().toImage();

    this->imgCore.RgbToGray(image);
    this->set_image(this->ui->image4label, image);

    this->setTables(
                this->ui->image4_1table,
                this->ui->image4_2table,
                this->ui->image4_3table,
                this->ui->image4label->pixmap().toImage(),
                this->ui->enegry_4,
                this->ui->entropiya_4,
                this->ui->contrast_4,
                this->ui->homo_4);
}


void SecondWindow::on_pushButton_clicked()
{
    QString homeDirectory = QString("/Users/gost/Documents");
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open Image"),
                homeDirectory,
                tr("Image Files (*.png *.jpg *.bmp *.jpeg)")
                );

    QPixmap openedImage(fileName);
    QImage image = openedImage.toImage();
    this->set_image(this->ui->image1label, image);
    image = this->ui->image1label->pixmap().toImage();

    this->imgCore.RgbToGray(image);
    this->set_image(this->ui->image1label, image);

    this->setTables(
                this->ui->image1_1table,
                this->ui->image1_2table,
                this->ui->image1_3table,
                this->ui->image1label->pixmap().toImage(),
                this->ui->enegry_1,
                this->ui->entropiya_1,
                this->ui->contrast_1,
                this->ui->homo_1);
}


void SecondWindow::on_pushButton_2_clicked()
{
    QString homeDirectory = QString("/Users/gost/Documents");
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open Image"),
                homeDirectory,
                tr("Image Files (*.png *.jpg *.bmp *.jpeg)")
                );

    QPixmap openedImage(fileName);
    QImage image = openedImage.toImage();
    this->set_image(this->ui->image2label, image);
    image = this->ui->image2label->pixmap().toImage();

    this->imgCore.RgbToGray(image);
    this->set_image(this->ui->image2label, image);

    this->setTables(
                this->ui->image_2_1_table,
                this->ui->image2_2table,
                this->ui->image2_3table,
                this->ui->image2label->pixmap().toImage(),
                this->ui->enegry_2,
                this->ui->entropiya_2,
                this->ui->contrast_2,
                this->ui->homo_3);
}


void SecondWindow::on_pushButton_3_clicked()
{
    QString homeDirectory = QString("/Users/gost/Documents");
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open Image"),
                homeDirectory,
                tr("Image Files (*.png *.jpg *.bmp *.jpeg)")
                );

    QPixmap openedImage(fileName);
    QImage image = openedImage.toImage();
    this->set_image(this->ui->image3label, image);
    image = this->ui->image3label->pixmap().toImage();


    this->imgCore.RgbToGray(image);
    this->set_image(this->ui->image3label, image);

    this->setTables(
                this->ui->image3_1_table,
                this->ui->image3_2table,
                this->ui->image3_3table,
                this->ui->image3label->pixmap().toImage(),
                this->ui->enegry_3,
                this->ui->entropiya_3,
                this->ui->contrast_3,
                this->ui->homo_6);
}


void SecondWindow::on_compareButton_clicked()
{
    double energy1 = this->ui->enegry_1->text().toDouble();
    double energy2 = this->ui->enegry_2->text().toDouble();
    double energy3 = this->ui->enegry_3->text().toDouble();
    double energy4 = this->ui->enegry_4->text().toDouble();

    double entropy1 = this->ui->entropiya_1->text().toDouble();
    double entropy2 = this->ui->entropiya_2->text().toDouble();
    double entropy3 = this->ui->entropiya_3->text().toDouble();
    double entropy4 = this->ui->entropiya_4->text().toDouble();

    double contrast1 = this->ui->contrast_1->text().toDouble();
    double contrast2 = this->ui->contrast_2->text().toDouble();
    double contrast3 = this->ui->contrast_3->text().toDouble();
    double contrast4 = this->ui->contrast_4->text().toDouble();

    double homo1 = this->ui->homo_1->text().toDouble();
    double homo2 = this->ui->homo_3->text().toDouble();
    double homo3 = this->ui->homo_6->text().toDouble();
    double homo4 = this->ui->homo_4->text().toDouble();

    this->ui->r12->setText(
                QString::number(this->lab01.R_compare(energy1, energy2,
                                      entropy1, entropy2,
                                      contrast1, contrast2,
                                      homo1, homo2)));
    this->ui->r34->setText(
                QString::number(this->lab01.R_compare(energy3, energy4,
                                      entropy3, entropy4,
                                      contrast3, contrast4,
                                      homo3, homo4)));

}


void SecondWindow::on_image2open_clicked()
{
    QString homeDirectory = QString("/Users/gost/Documents");
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open Image"),
                homeDirectory,
                tr("Image Files (*.png *.jpg *.bmp *.jpeg)")
                );

    QPixmap openedImage(fileName);
    QImage image = openedImage.toImage();

    this->set_image(this->ui->image2label_2, image);
    image = this->ui->image2label->pixmap().toImage();
}



void SecondWindow::on_thinButton_clicked()
{
    QPixmap qpix = this->ui->image2label_2->pixmap();
    QImage qimg = qpix.toImage();
    int** baseMatrix = this->lab02.GetBaseMatrix(qimg);

    int** thinnerZeros = this->lab02.ZongSune(baseMatrix, qimg.width(), qimg.height());

    int** thinner = this->lab02.FromZerosToRGB(thinnerZeros, qimg.width(), qimg.height());

    QPixmap thinnerPixmap(qimg.width(), qimg.height());

    QImage thinnerImage = thinnerPixmap.toImage();

    for (int x = 0; x < qimg.width(); x++)
    {
        for (int y = 0; y < qimg.height(); y++)
        {
            thinnerImage.setPixel(x, y, QColor(thinner[x][y], thinner[x][y], thinner[x][y]).rgb());
        }
    }

    this->set_image(this->ui->image2label_2, thinnerImage);

}

