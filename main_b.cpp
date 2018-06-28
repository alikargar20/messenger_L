#include "main_b.h"
#include "getlist.h"
#include "ui_main_b.h"
#include"loginpage.h"
#include "ui_loginpage.h"


Main_b::Main_b(QString token, QString user , QString pass ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Main_b)
{
    this->token=token;
    this->username = user;
    this->password = pass;
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    manage = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&Main_b::Reply);
    connect(manage,&QNetworkAccessManager::finished,this,&Main_b::on_searchBut_reply);



    url = new SetQuery;
    url->setToken(token);

    central_scroll_area = new QWidget;
    layout_scroll_area = new QVBoxLayout(central_scroll_area);
    layout_scroll_area->setAlignment(central_scroll_area,Qt::AlignBottom);
   // layout_scroll_area->setStretch(1000,1000);

}

Main_b::~Main_b()
{
    delete ui;
}





void Main_b::on_searchBut_clicked()
{
    str_id = ui->search->text();
    req.setUrl(url->setGetUserChatsQuery(str_id));
    manage->get(req);

}


void Main_b::on_searchBut_reply(QNetworkReply  *repl){
    QString rep_str = repl->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(rep_str.toUtf8());
    QJsonObject jobj = jdoc.object();
   // qDebug()<<jobj["message"].toString();
    if(jobj["code"].toString() == "200"){
        ui->search->setText("");
        ui->label->setText(str_id);

    }


}

void Main_b::on_logout_clicked()
{
    req.setUrl( url -> setLogOutQuery(username ,password));
    manager ->get(req);


}


void Main_b ::Reply(QNetworkReply * rep){

    QString str = rep ->readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(str.toUtf8());
    QJsonObject obj=jdoc.object();
    if(obj["code"].toString() == "200"){
        LoginPage *log = new LoginPage;
        setCentralWidget(log);
        log->setGeometry(300,40,795,715);
        log->show();

       //this -> hide();
    }


}

void Main_b::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return){
        on_send_clicked();
    }

}



void Main_b::on_send_clicked()

{

        QString str_mess = ui->typekon->text();
        SendRecieveMess send_obj;
        send_obj.send_user(str_id , str_mess , token);
        ui->typekon->setText("");
        ui->scrollArea->setWidget(central_scroll_area);
        ui->scrollArea->setWidgetResizable(true);
        QLabel *label1 = new QLabel(str_mess);
        label1->setFixedHeight(25);
        label1->setAlignment(Qt::AlignRight);
        layout_scroll_area->addWidget(label1);


}

