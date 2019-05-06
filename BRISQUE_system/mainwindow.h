#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <qdebug.h>
#include <QDateTime>
#include "brisque.h"
#include "svm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QFileDialog *fileDialog;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem;
    QFileInfoList fileList;

    Mat QImage2cvMat(QImage image);

    int currentFileIndex;
    bool getDisplayedImage(QImage&) const;
    void showImage(QImage);
    void showLog(QString str);
    void open();
    void upload();

public slots:
    void on_open_clicked();
    void on_upload_clicked();

};

#endif // MAINWINDOW_H
