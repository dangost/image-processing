#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "point.h"
#include <QFileDialog>
#include <QByteArrayView>
#include <QGridLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>


SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow),
    imgCore(),
    lab01(),
    lab02()
{

    ui->setupUi(this);

    // QChart *chart = new QChart();

    // this->gridLayout = new QGridLayout(this->ui->pointsWidget);

    // this->chartView = new QChartView(chart);
    //this->gridLayout->addWidget(this->chartView);

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
    QString homeDirectory = QString("/home/gost/Documents");
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

    int** baseMatrix = this->lab02.GetBaseMatrix(image);
    int w = image.width();
    int h = image.height();
    this->setTable(this->ui->baseTable_2, baseMatrix, w, h, false);

}

void SecondWindow::setTable(QTableWidget *table, int** matrix, int width, int height, bool color = false)
{
    table->setRowCount(height);
    table->setColumnCount(width);

    for (int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            auto item = new QTableWidgetItem();
            item->setText(QString::number(matrix[x][y]));

            if (matrix[x][y] == 2 && color)
            {
                item->setBackground(Qt::yellow);
            }
            else if(matrix[x][y] >= 3 && color)
            {
                item->setBackground(Qt::green);
            }
            else if(matrix[x][y] == 1 && color)
            {
                item->setBackground(Qt::cyan);
            }
            table->setItem(y, x, item);
        }
    }
}



void SecondWindow::on_thinButton_clicked()
{
    QPixmap qpix = this->ui->image2label_2->pixmap();
    QImage qimg = qpix.toImage();
    int** baseMatrix = this->lab02.GetBaseMatrix(qimg);

    int** thinnerZeros = this->lab02.ZongSune(baseMatrix, qimg.width(), qimg.height());

    QPixmap thinnerPixmap(qimg.width(), qimg.height());

    QImage thinnerImage = thinnerPixmap.toImage();

    this->setTable(this->ui->thinnerTable, thinnerZeros, thinnerImage.width(), thinnerImage.height());

    int** thinner = this->lab02.FromZerosToRGB(thinnerZeros, qimg.width(), qimg.height());
    for (int x = 0; x < qimg.width(); x++)
    {
        for (int y = 0; y < qimg.height(); y++)
        {
            thinnerImage.setPixel(x, y, QColor(thinner[x][y], thinner[x][y], thinner[x][y]).rgb());
        }
    }

    this->set_image(this->ui->image2label_2, thinnerImage);
}


void SecondWindow::on_cnButton_clicked()
{
    int width = 50;
    int height = 50;
    int** thin = new int*[width];
    for (int i = 0; i < width; i++)
    {
        thin[i] = new int[height];
        for(int j = 0; j < height; j++)
        {
            thin[i][j] = this->ui->thinnerTable->item(j, i)->text().toInt();
        }
    }

    int** cnmatrix = this->lab02.CNMatrix(thin, width, height);

    this->setTable(this->ui->cnTable, cnmatrix, width, height, true);
}


void SecondWindow::on_scanbutton_clicked()
{
    QString path = "/home/gost/pets/image-processing/imgp/letters";
    QDir imagesDir(path);

    QList<LetterData> letters;
    this->dataset = new LetterPointsDataset();
    this->new_points.clear();

    int index = 0;
    for(QString &filename : imagesDir.entryList(QDir::Files))
    {
        QPixmap openedImage(path + "/" + filename);
        QImage image = openedImage.toImage();
        filename.replace(".png", "");
        letters.append(this->processImage(image, 50, 50, index, filename.toStdString()));
        index++;
    }

    this->fillDataSetTable(letters);
}

void SecondWindow::fillDataSetTable(QList<LetterData> list)
{
    this->ui->datasetTable->setRowCount(list.length() + 10);
    this->ui->datasetTable->setColumnCount(4);

    // fill head
    auto tableitem = new QTableWidgetItem();
    tableitem->setText("Index");
    this->ui->datasetTable->setItem(0, 0, tableitem);

    tableitem = new QTableWidgetItem();
    tableitem->setText("Knotes");
    this->ui->datasetTable->setItem(0, 1, tableitem);

    tableitem = new QTableWidgetItem();
    tableitem->setText("Ends");
    this->ui->datasetTable->setItem(0, 2, tableitem);

    tableitem = new QTableWidgetItem();
    tableitem->setText("Class👍");
    this->ui->datasetTable->setItem(0, 3, tableitem);

    this->series1 = new QScatterSeries();
    series1->setName("Е");
    series1->setMarkerSize(10.0);
    series1->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series1->setColor(Qt::cyan);


    this->series2 = new QScatterSeries();
    series2->setName("M");
    series2->setMarkerSize(10.0);
    series2->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series2->setColor(Qt::green);

    this->series3 = new QScatterSeries();
    series3->setName("Щ");
    series3->setMarkerSize(10.0);
    series3->setMarkerShape(QScatterSeries::MarkerShapeTriangle);
    series3->setColor(Qt::red);


    int i = 1;
    for (LetterData item : list)
    {
        if (item.klass.find("Е") != std::string::npos)
        {
            series1->append(item.ends, item.knotes);
            this->dataset->add_E(Point(item));
        }

        else if (item.klass.find("М") != std::string::npos)
        {
            series2->append(item.ends, item.knotes);
            this->dataset->add_M(Point(item));
        }

        else if (item.klass.find("Щ") != std::string::npos)
        {
            series3->append(item.ends, item.knotes);
            this->dataset->add_W(Point(item));
        }

        else
        {
            this->new_points.append(item);
            continue;
        }

        tableitem = new QTableWidgetItem();
        tableitem->setText(QString::number(item.index));

        this->ui->datasetTable->setItem(i, 0, tableitem);

        tableitem = new QTableWidgetItem();
        tableitem->setText(QString::number(item.knotes));
        this->ui->datasetTable->setItem(i, 1, tableitem);

        tableitem = new QTableWidgetItem();
        tableitem->setText(QString::number(item.ends));
        this->ui->datasetTable->setItem(i, 2, tableitem);

        tableitem = new QTableWidgetItem();
        tableitem->setText(QString::fromStdString(item.klass));
        this->ui->datasetTable->setItem(i, 3, tableitem);
        i++;
    }

    this->drawChart(QList<QScatterSeries*>{this->series1, this->series2, this->series3});
}

void SecondWindow::drawChart(QList<QScatterSeries*> series)
{
    this->ui->pointsWidget = new QWidget(this->ui->tab_7);
    this->ui->pointsWidget->setObjectName(QString::fromUtf8("pointsWidget"));
    this->ui->pointsWidget->setGeometry(QRect(10, 50, 670, 670));
    this->ui->pointsWidget->setMinimumSize(QSize(500, 500));
    this->ui->pointsWidget->setMaximumSize(QSize(800, 800));
    this->ui->pointsWidget->show();

    QChart *chart = new QChart();
    for (QScatterSeries *ser : series)
    {
        chart->addSeries(ser);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).back()->setRange(-0.5, 6);
    chart->axes(Qt::Horizontal).back()->setTitleText("ends");

    chart->axes(Qt::Vertical).back()->setRange(-0.5, 6);
    chart->axes(Qt::Vertical).back()->setTitleText("knotes");

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setDropShadowEnabled(false);

    this->gridLayout = new QGridLayout();



    this->chartView = new QChartView(chart);
    this->gridLayout->addWidget(this->chartView);
    this->ui->pointsWidget->setLayout(this->gridLayout);

}


void SecondWindow::on_recButton_clicked()
{
    int i = this->dataset->E_class.count() + this->dataset->W_class.count() + this->dataset->M_class.count() + 1;
    for (LetterData item : this->new_points)
    {
        item.index = i;
        auto point = Point(item);

        auto klass = this->dataset->findClass(point);
        item.klass = klass.toStdString();

        auto tableitem = new QTableWidgetItem();
        tableitem->setText(QString::number(item.index));

        this->ui->datasetTable->setItem(i, 0, tableitem);

        tableitem = new QTableWidgetItem();
        tableitem->setText(QString::number(item.knotes));
        this->ui->datasetTable->setItem(i, 1, tableitem);

        tableitem = new QTableWidgetItem();
        tableitem->setText(QString::number(item.ends));
        this->ui->datasetTable->setItem(i, 2, tableitem);

        tableitem = new QTableWidgetItem();
        tableitem->setText(QString::fromStdString(item.klass));
        this->ui->datasetTable->setItem(i, 3, tableitem);

        if (klass == "Е")
        {
            this->dataset->add_E(point);
            this->series1->append(point.x, point.y);
        }
        else if (klass == "М")
        {
            this->dataset->add_M(point);
            this->series2->append(point.x, point.y);
        }
        else if (klass == "Щ")
        {
            this->dataset->add_W(point);
            this->series3->append(point.x, point.y);
        }

    }


    this->on_centerButton_clicked();
}


void SecondWindow::on_centerButton_clicked()
{
    this->dataset->init_centers();

    QScatterSeries *e_center = new QScatterSeries();
    e_center->setName("cE");
    e_center->setMarkerSize(40.0);
    e_center->setMarkerShape(QScatterSeries::MarkerShapeStar);
    e_center->setColor(Qt::cyan);

    QScatterSeries *w_center = new QScatterSeries();
    w_center->setName("cЩ");
    w_center->setMarkerSize(40.0);
    w_center->setMarkerShape(QScatterSeries::MarkerShapeStar);
    w_center->setColor(Qt::red);

    QScatterSeries *m_center = new QScatterSeries();
    m_center->setName("cМ");
    m_center->setMarkerSize(40.0);
    m_center->setMarkerShape(QScatterSeries::MarkerShapeStar);
    m_center->setColor(Qt::green);

    e_center->append(this->dataset->E_center->x, this->dataset->E_center->y);
    w_center->append(this->dataset->W_center->x, this->dataset->W_center->y);
    m_center->append(this->dataset->M_center->x, this->dataset->M_center->y);

    this->drawChart(
                QList<QScatterSeries*> {
                    this->series1, this->series2, this->series3,
                    e_center, w_center, m_center
                });
}

void SecondWindow::recognizeLetter(LetterData letter_data)
{

}


LetterData SecondWindow::processImage(QImage image, int w, int h, int index, std::string klass)
{
    int** base = this->lab02.GetBaseMatrix(image);
    int** thin = this->lab02.ZongSune(base, w, h);

    int** cnmatrix = this->lab02.CNMatrix(thin, w, h);

    int knotes = 0;
    int ends = 0;

    for (int i = 0 ; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (cnmatrix[i][j] >= 3)
            {
                knotes++;
            }
            else if (cnmatrix[i][j] == 1)
            {
                ends++;
            }
        }
    }


    return LetterData(index, knotes, ends, klass);
}




