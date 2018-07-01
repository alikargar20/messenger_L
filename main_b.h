#ifndef MAIN_B_H
#define MAIN_B_H

#include <QMainWindow>
#include"loginpage.h"
#include "ui_loginpage.h"
#include "thread.h"
#include "loginpage.h"
#include <QApplication>
#include<QPainter>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include"register.h"
#include"sendrecievemess.h"
#include<QScrollArea>
#include<QVBoxLayout>
#include<QScrollBar>
#include<QKeyEvent>
#include<QThread>
#include<QMessageBox>
#include"creation.h"
namespace Ui {
class Main_b;
}

class Main_b :  public QMainWindow
{
    Q_OBJECT

public:
    explicit Main_b( QString token , QString user , QString pass , QWidget *parent = 0);
    ~Main_b();
    void Reply(QNetworkReply * rep);
    //friend class GetList;
    Thread *mThread;
    Thread *hThread;
    QNetworkAccessManager *channel_create_net;
    QNetworkAccessManager *group_create_net;

protected:
    Ui::Main_b *ui;
    QNetworkAccessManager *manager;
    QNetworkAccessManager *manage;

    QNetworkAccessManager *n;
    QNetworkRequest  req;
    QString token;
    SetQuery * url;
    QNetworkReply * rep;
    QString username;
    QString password;
    QString str_id;
    QString sum_str = "";
    QWidget *central_scroll_area;
    QVBoxLayout *layout_scroll_area;
    QScrollBar *scrollbar_in_scrollarea;
    QThread thread;
    QThread thread2;
    void keyPressEvent(QKeyEvent *event);
    void set_mess_groupCre(QNetworkReply * r);
    void set_mess_channelCre(QNetworkReply * r);
public slots:
    void search_reply(QNetworkReply *repl);
    void thread_rec();
private slots:


    void on_searchBut_clicked();
    void on_send_clicked();
    void on_pushButton_clicked();
};

#endif // MAIN_B_H
