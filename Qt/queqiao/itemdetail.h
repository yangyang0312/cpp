#ifndef ITEMDETAIL_H
#define ITEMDETAIL_H

#include <QMainWindow>
#include "queqiaostruct.h"
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class itemdetail;
}

class itemdetail : public QMainWindow
{
    Q_OBJECT

public:
    explicit itemdetail(QWidget *parent = 0);
    ~itemdetail();

private:
    Ui::itemdetail *ui;
    void open_browser(const QString &url);
    void update_window();
    QString get_tk_level(int);
    QString get_remain_days(int endTime);
    QString get_time(int start,int end);
    Table item;
    QString log;
    void log_ch(QString);
    QString temp_html;//存复制模板的html

private slots:
    void on_need_detail(Table);
    void on_item_detail_open_clicked();
    void on_item_href_open_clicked();
    void on_dwz_open_clicked();
    void on_event_info_open_clicked();
    void on_event_detail_open_clicked();
    void closeEvent(QCloseEvent*event);
    void on_event_info_copy_clicked();
    void on_copy_clicked();
    void on_imagin_complete();
    void on_item_href_copy_clicked();
    void on_item_complete(Item);
    void on_dwz_complete(QString);
    void on_pid_updated(QList<Pid>,QString);
    void on_update_pid_clicked();
    void on_dwz_copy_clicked();
    void on_item_title_copy_clicked();
    void on_item_detail_copy_clicked();
    void on_event_detail_copy_clicked();

    void on_copy_char_clicked();

signals:
    void log_changed(QString);
    void need_item(QString,QString,QString);
    void pid_need_update();
};

#endif // ITEMDETAIL_H
