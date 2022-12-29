#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/* https://fairyonice.github.io/2D-DCT.html -> dct matrix equation
 * https://web.archive.org/web/20180421030430/http://www.equasys.de/colorconversion.html -> YCbCr/Rgb format equations
 * https://www.youtube.com/watch?v=CAn-FzQkGTA -> dct matrix equation video
 *
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_imageButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    struct YCbCrFormat ColorSpaceConversion(int red, int green, int blue); // lossless conversion
    QColor ReversedColorSpaceConversion(int Y, int Cb, int Cr);

    void ChrominanceDownsampling(int* blueChrom, int* redChrom, int width, int height);

    void DiscreteCosineTransform(int* lum, int* blueChrom, int* redChrom, int width, int height); // DCT

    void performCompression(QImage* image);

    int* Luminance;
    int* BlueChrominance;
    int* RedChrominance;

    float* dctMatrix;

    QImage* currentImage = nullptr;
};
#endif // MAINWINDOW_H
