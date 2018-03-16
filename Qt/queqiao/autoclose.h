#ifndef AUTOCLOSE
#define AUTOCLOSE

#include <QTimer>
#include <QObject>
#include <QPushButton>
#include <QMessageBox>

class AutoClose:public QObject
{
    Q_OBJECT
public:
    QMessageBox*box;
    QPushButton*yesBtn;
    QPushButton*noBtn;
    QPushButton*cancleBtn;

    AutoClose(const QString &title,const QString &content,int time)
    {
        box=new QMessageBox();

        //QTimer::singleShot(time,box,SLOT(close()));

        box->setIcon(QMessageBox::NoIcon);
        box->setWindowTitle(title);
        box->setText(content);

        yesBtn=box->addButton("是(&Y)",QMessageBox::YesRole);
        noBtn=box->addButton("否(&N)",QMessageBox::NoRole);
        cancleBtn=box->addButton("取消(&cancle)",QMessageBox::NoRole);
        //box->show();
        QTimer::singleShot(time,yesBtn,SLOT(click()));
       // QTimer *timer = new QTimer();
        //timer->start(time);
        //connect(timer, SIGNAL(timeout()),yesBtn,SLOT(click()));
    }

    ~AutoClose()
    {
        delete box;
        delete yesBtn;
        delete noBtn;
        delete cancleBtn;
    }

    void show()
    {
        box->show();
    }
};


#endif // AUTOCLOSE
