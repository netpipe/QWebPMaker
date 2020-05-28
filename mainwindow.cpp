#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "img2webp.h"
#include <QDebug>
#include <QFileDialog>
#include <QDirIterator>
#include <QFile>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFileInfo>

#include <stdio.h>
#include <string.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//static void Help(void) {
//  printf("Usage:\n\n");
//  printf("  img2webp [file-level options] [image files...] "
//         "[per-frame options...]\n");
//  printf("\n");

//  printf("File-level options (only used at the start of compression):\n");
//  printf(" -min_size ............ minimize size\n");
//  printf(" -loop <int> .......... loop count (default: 0, = infinite loop)\n");
//  printf(" -kmax <int> .......... maximum number of frame between key-frames\n"
//         "                        (0=only keyframes)\n");
//  printf(" -kmin <int> .......... minimum number of frame between key-frames\n"
//         "                        (0=disable key-frames altogether)\n");
//  printf(" -mixed ............... use mixed lossy/lossless automatic mode\n");
//  printf(" -v ................... verbose mode\n");
//  printf(" -h ................... this help\n");
//  printf(" -version ............. print version number and exit\n");
//  printf("\n");

//  printf("Per-frame options (only used for subsequent images input):\n");
//  printf(" -d <int> ............. frame duration in ms (default: 100)\n");
//  printf(" -lossless  ........... use lossless mode (default)\n");
//  printf(" -lossy ... ........... use lossy mode\n");
//  printf(" -q <float> ........... quality\n");
//  printf(" -m <int> ............. method to use\n");

//  printf("\n");
//  printf("example: img2webp -loop 2 in0.png -lossy in1.jpg\n"
//         "                  -d 80 in2.tiff -o out.webp\n");
//  printf("\nNote: if a single file name is passed as the argument, the "
//         "arguments will be\n");
//  printf("tokenized from this file. The file name must not start with "
//         "the character '-'.\n");
//}

void MainWindow::on_pushButton_clicked()
{

  //QString  fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "JPEG (*.jpg);;PNG (*.png)" );
    QString fileName = QFileDialog ::getOpenFileName(0,"Select File","","JPEG (*.jpg);;PNG (*.png)" );

    qDebug() << "testing";

   // const char *argv1[]={"appname","-d","800","-loop","2","in0.bmp","-lossy","in1.bmp","-o","test.webp","null"};

QFileInfo fileInfo(fileName);
QString webpoutfile = QDir(fileInfo.absolutePath()).filePath(fileInfo.baseName()).toLatin1()+".webp";
qDebug() << webpoutfile.toLatin1();


  //  char *argv1[]={"appname","-lossy",fileName.toLocal8Bit().data(),"-o",webpoutfile.toLocal8Bit().data(),"null"};
    const char *argv1[]={"appname","-lossy",fileName.toLocal8Bit().data(),"-o",webpoutfile.toLocal8Bit().data(),"null"};
// const char *argv1[]={"appname","in1.bmp","in0.bmp","null"};

     int argc1 = sizeof(argv1) / sizeof(char*) - 1;

     //const char** p = const_cast<const char**>(argv1);
     //int argc1 = sizeof(argv1) / sizeof(char*) - 1;

     QImage *img_object = new QImage();
     img_object->load(fileName);
     QPixmap image = QPixmap::fromImage(*img_object);
  //   QPixmap scaled_img = image.scaled(this->width(), this->height(), Qt::KeepAspectRatio);
     QPixmap scaled_img = image.scaled(ui->graphicsView->width(), ui->graphicsView->height(), Qt::KeepAspectRatio);
     QGraphicsScene *scene= new QGraphicsScene();
    // scene->addItem(new QGraphicsSvgItem("./tmp.svg"));
     scene->addPixmap(scaled_img);
     scene->setSceneRect(scaled_img.rect());
     ui->graphicsView->setScene(scene);
     ui->graphicsView->show();


     img2webp(argc1,argv1);
}

void MainWindow::on_batchbutton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());

    QDirIterator it(directory.toLatin1(), QStringList() << "*.jpg", QDir::Files, QDirIterator::Subdirectories);
    QStringList files;

    while (it.hasNext()){
      //  QFileInfo fileInfo(f.fileName());
        files << it.next().toLatin1();
        qDebug() << '"' + it.next().toLatin1() + '"';
    }

    QStringList fileslist;
    //QString fileslist;
    fileslist.append("blank");

    for (int i=0; i < files.size() ; i++)
    {
        fileslist.append(files.at(i).toLatin1() );
        ui->listWidget->addItem(files.at(i).toLatin1());
        qDebug() << files.at(i).toLatin1();
    }
        fileslist.append("-o");
        // QString  fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "JPEG (*.jpg);;PNG (*.png)" );

    fileslist.append("movie.webm");
    fileslist.append("blank");

//https://forum.qt.io/topic/28723/solved-constructing-c-string-array-const-char-from-qstringlist
 //   int size = fileslist.size();
 //   char *argv1[size];
  //  int i=0;
  //  foreach(QString s, fileslist)
 //   {
   // c[i] = s.toLocal8Bit().constData();
 //   argv1[i] = new char[s.toLocal8Bit().size()];
 //   strcpy(argv1[i],s.toLocal8Bit().constData());
   // i++;
   // }


 //couple of examples for converting char*'s
      //  const char *str;
       //  QString path;
        //  QByteArray ba;
        // ba = path.toLatin1();
        //                str = fileslist.join(",").toUtf8();
          //              printf("the string path will be:%s\n", str);

    //QString str("abcd");
    //QByteArray br = str.toUtf8();

 // qDebug() << QByteArray(test, sizeof(test));
// qDebug() << QByteArray::fromRawData(test, sizeof(test))


QString test2;
    const char *argv2[]={"appname","-lossy","in0.jpg","-o","webp.webp","\0"};

    int length = sizeof(argv2) / sizeof(char*) - 1;
   // qDebug() << sizeof(&test);
       qDebug() << length;

    for (int i=0; i < length;i++){
        test2.append(argv2[i]);
        test2.append(",");
    }
    test2.append("blank");
 qDebug() << test2.toLatin1();

   //const char *argv1[]={fileslist.join(",").toUtf8()};
   // const char** p = const_cast<const char**>(argv1);

 QStringList splitlist = test2.split(",");
 //int i = splitlist.size
 const char* splitlist2[splitlist.size()];
 for (int i=0; i < splitlist.size() ; i++){
     splitlist[i] = splitlist.at(i).toUtf8();
 }

 //const char *argv1[]={test2.toUtf8()};

     int argc1 = sizeof(splitlist2) / sizeof(char*) - 1;

     //const_cast<const char**>(argv1)
     img2webp(argc1,splitlist2);

}

void MainWindow::on_pushButton_2_clicked()
{

    QString test2;
        const char *argv2[]={"appname","-lossy","in0.jpg","-o","webp.webp","null"};

        int length = sizeof(argv2) / sizeof(char*);
       // qDebug() << sizeof(&test);
           qDebug() << length;

        for (int i=0; i < length;i++){
            test2.append(argv2[i]);
            if (i < length-1){  test2.append(",");}

                 qDebug() << argv2[i];
        }
      // test2.append("null");
     qDebug() << test2.toLatin1();

       //const char *argv1[]={fileslist.join(",").toUtf8()};
       // const char** p = const_cast<const char**>(argv1);

     QStringList splitlist = test2.split(",");
     //int i = splitlist.size
     const char* splitlist2[splitlist.size()];
     for (int i=0; i < splitlist.size() ; i++){
         splitlist[i] = splitlist.at(i).toUtf8();
         qDebug() << splitlist.at(i).toUtf8();
     }

     //const char *argv1[]={test2.toUtf8()};
         int argc2 = sizeof(splitlist2) / sizeof(char*) - 1;
         qDebug() << argc2;
         int argc1 = sizeof(argv2) / sizeof(char*) - 1;
           qDebug() << argc1;
         //const_cast<const char**>(argv1)
         img2webp(argc2,splitlist2);
        // img2webp(argc1,argv2);
}
