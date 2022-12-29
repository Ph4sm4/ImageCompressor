#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QFileDialog>
#include <QDebug>
#include <QGraphicsScene>
#include "YCbCrFormat.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

YCbCrFormat MainWindow::ColorSpaceConversion(int red, int green, int blue)
{
    int Y = round(0.299 * red + 0.587 * green + 0.114 * blue); // luminance
    int BlueChrominance = round(-0.1687 * red - 0.3313 * green + 0.5 * blue + 128);
    int RedChrominance = round(0.5 * red - 0.4187 * green - 0.0813 * blue + 128);

    /*
     * colors contained in an image are called chrominance
     * whereas luminance stands for brightness and darkness
     */
    YCbCrFormat output(Y, BlueChrominance, RedChrominance);

    return output;
}

QColor MainWindow::ReversedColorSpaceConversion(int Y, int Cb, int Cr)
{
    int red = round(1.0f * Y + 1.4 * (Cr - 128));
    int green = round(1.0f * Y - 0.343 * (Cb - 128) - 0.711 * (Cr - 128));
    int blue = round(1.0f * Y + 1.765 * (Cb - 128));

    return QColor(red, green, blue);
}

void MainWindow::ChrominanceDownsampling(int *blueChrom, int *redChrom, int width, int height)
{
    for(int i = 0; i < width; i += 2) {
        for(int j = 0; j < height; j += 2) {
            int bC1 = blueChrom[i * height + j];
            int bC2 = blueChrom[(i + 1) * height + j];
            int bC3 = blueChrom[i * height + j + 1];
            int bC4 = blueChrom[(i + 1) * height + j + 1];

            int rC1 = redChrom[i * height + j];
            int rC2 = redChrom[(i + 1) * height + j];
            int rC3 = redChrom[i * height + j + 1];
            int rC4 = redChrom[(i + 1) * height + j + 1];

            int averageBlueChrom = round((bC1 + bC2 + bC3 + bC4) / 4);
            int averageRedChrom = round((rC1 + rC2 + rC3 + rC4) / 4);

            blueChrom[i * height + j] = averageBlueChrom;
            blueChrom[(i + 1) * height + j] = averageBlueChrom;
            blueChrom[i * height + j + 1] = averageBlueChrom;
            blueChrom[(i + 1) * height + j + 1] = averageBlueChrom;

            redChrom[i * height + j] = averageRedChrom;
            redChrom[(i + 1) * height + j] = averageRedChrom;
            redChrom[i * height + j + 1] = averageRedChrom;
            redChrom[(i + 1) * height + j + 1] = averageRedChrom;
        }
    }
}

void MainWindow::DiscreteCosineTransform(int* lum, int* blueChrom, int* redChrom, int width, int height)
{
    dctMatrix = new float [width * height];
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            if(i == 0) {

            }
        }
    } // create the dct matrix first

    for(int i = 0; i < width; i += 8) {
        for(int j = 0; j < height; j += 8) {
            lum[i * height + j] -= 128;
        }
    }
}

void MainWindow::performCompression(QImage *image)
{
    const int width = image->size().width();
    const int height = image->size().height();

    Luminance = new int [width * height];
    BlueChrominance = new int [width * height];
    RedChrominance = new int [width * height];

    // array[i][j] is then rewritten as
    //array[i*height+j]


    // reading pixel data and converting them to YCbCr format
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            QColor pix = image->pixelColor(i, j);
            YCbCrFormat values = ColorSpaceConversion(pix.red(), pix.green(), pix.blue());

            Luminance[i * height + j] = values.luminance;
            BlueChrominance[i * height + j] = values.blueChrominance;
            RedChrominance[i * height + j] = values.redChrominance;
        }
    }


    ChrominanceDownsampling(BlueChrominance, RedChrominance, width, height);
}


void MainWindow::on_imageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose an image to compress"), "", tr("Images (*.png *.jpg *.jpeg *bmp *gif"));

    if(fileName == "") return;

    qDebug() << fileName;

    QImage image;
    bool valid = image.load(fileName);

    if(valid) {
           QGraphicsScene* scene = new QGraphicsScene();
           scene->addPixmap(QPixmap::fromImage(image));
           ui->imageDisplayer->setScene(scene);
           ui->imageDisplayer->show(); // loading the image into the graphics view

           currentImage = &image;
    }
    else {
        qDebug() << "failed to load the image";
    }
}


void MainWindow::on_pushButton_clicked()
{
    performCompression(currentImage);
}

