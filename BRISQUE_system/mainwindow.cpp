#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileDialog(new QFileDialog(this)),
    scene(NULL),pixmapItem(NULL),
    currentFileIndex(-1)

{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileDialog;
    delete pixmapItem;
    delete scene;
}

void MainWindow::showImage(QImage img)
{
    if(pixmapItem)
    {
        delete pixmapItem;
        pixmapItem = NULL;
    }
    if(scene)
    {
        delete scene;
        scene = NULL;
    }

    pixmapItem = new QGraphicsPixmapItem();
    pixmapItem->setPixmap(QPixmap::fromImage(img));

    scene = new QGraphicsScene(this);
    scene->addItem(pixmapItem);

    ui->graphicsView->setScene(scene);
}

Mat MainWindow::QImage2cvMat(QImage image)
{
    cv::Mat mat;
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.bits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.bits(), image.bytesPerLine());
        break;
    }
    return mat;
}

bool MainWindow::getDisplayedImage(QImage &img) const
{
    QList<QGraphicsItem *> items=ui->graphicsView->scene()->items();//获得场景中的所有物品
    //需要判断是否打开文件
    if(items.size()==0)return false;
    QGraphicsPixmapItem* item=(QGraphicsPixmapItem*)items.at(0);
    img=item->pixmap().toImage();
    return true;
}


void MainWindow::open()
{
   if(fileDialog->exec())
    {
        QStringList files =  fileDialog->selectedFiles();
        QDir dir=fileDialog->directory();
        QStringList filters;
        filters<<"*.bmp"<<"*.jpg"<<"*.png";
        fileList=dir.entryInfoList(filters);
        for(int i=0;i<fileList.size();++i)
        {/*
            if(fileList[i].absoluteFilePath()==files[0])
           {
                currentFileIndex=i;
                break;
            }*/
            //float qualityscore;
            //Mat img2=QImage2cvMat(img);
            //Mat img2=imread("F:/BRISQUE/BRISQUE/BRISQUE/images/img3.jpg");
            //QString filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg)"));
            showImage(QImage(fileList[i].absoluteFilePath()));
            stringstream ss;
            ss<<fileList.at(i).absoluteFilePath().toStdString()<<endl;
            Mat img2=imread(fileList.at(i).absoluteFilePath().toStdString());

            float qualityscore = computescore(img2);

            ss<<"Quality Score:"<<qualityscore<<"\n";
            showLog(ss.str().c_str());
        }

   }
}

void MainWindow::upload()
{
    float qualityscore;
    //Mat img2=QImage2cvMat(img);
    //Mat img2=imread("F:/BRISQUE/BRISQUE/BRISQUE/images/img3.jpg");
    QString filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg)"));
    showImage(QImage(filename));
    stringstream ss;
    ss<<filename.toStdString()<<endl;
    Mat img2=imread(filename.toStdString());
    //imshow("image",img2);

    qualityscore = computescore(img2);

    ss<<"Quality Score:"<<qualityscore<<"\n";
    showLog(ss.str().c_str());

}



void MainWindow::on_open_clicked()
{
   open();
}

void MainWindow::on_upload_clicked()
{
   upload();
}
void MainWindow::showLog(QString str)
{
    QDateTime current_date_time=QDateTime::currentDateTime();
    QString current_date=current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz");
    QString info=ui->textEdit->toPlainText();
    info.append("[********").append(current_date).append("*******]\n").append(str);
    ui->textEdit->setText(info);
}


