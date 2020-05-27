#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "img2webp.h"
#include <QDebug>
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
//    img2webp -loop 2 in0.png -lossy in1.jpg
    //\n -d 80 in2.tiff -o out.webp\n");

    //ui->XZINGformat->currentText().toLocal8Bit().data(),fileName.toLocal8Bit().data()

    qDebug() << "testing";

   // const char *argv1[]={"appname","-d","800","-loop","2","in0.bmp","-lossy","in1.bmp","-o","test.webp","null"};

    const char *argv1[]={"appname","-d","800","-loop","2","in0.jpg","-lossy","in1.jpg","-o","test.webp","null"};

// const char *argv1[]={"appname","in1.bmp","in0.bmp","null"};
     int argc1 = sizeof(argv1) / sizeof(char*) - 1;

     img2webp(argc1,argv1);
}
