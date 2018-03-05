#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_bLeftBtnPress = false;
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);    //去掉标题栏
    m_pixmap.load(":/img/plant.png");           //加载
    resize(m_pixmap.size());                    //设置窗口大小为图片大小

    // 方法一：
    /*
    setAutoFillBackground(true);                //设置自动填充
    setMask(m_pixmap.mask());                   //设置图片透明的地方为穿透
    */

    // 方法二：
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("image: url(:/img/plant.png);");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)      //绘制
{
    /*
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background,m_pixmap);
    setPalette(palette);
    */
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_ptPress = event->globalPos();         //记录按下位置
        m_bLeftBtnPress = true;
    }
    event->ignore();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bLeftBtnPress)                         //移动窗口
    {
        move(pos() + event->globalPos() - m_ptPress);
        m_ptPress = event->globalPos();
    }
    event->ignore();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        m_bLeftBtnPress = false;
    event->ignore();
}
