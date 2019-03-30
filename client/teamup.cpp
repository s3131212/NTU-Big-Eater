#include "teamup.h"
#include "ui_teamup.h"
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QListWidget>
#include <restaurant.h>
#include <QMessageBox>
#include <string>

TeamUp::TeamUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeamUp)
{
    ui->setupUi(this);
    TeamUp::setWindowTitle("揪團吃！");
}

TeamUp::~TeamUp()
{
    delete ui;
    delete teamup;
    delete manager;
}

void TeamUp::getList(){
	manager = new QNetworkAccessManager();
	QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(managerGetListFinished(QNetworkReply*)));
	request.setUrl(QUrl("http://127.0.0.1:8080/?action=get"));
	manager->get(request);
}

void TeamUp::managerGetListFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
	}

	QByteArray response = reply->readAll();

	if(response == "[]")
		return ;

    QJsonParseError jsonError;
	QJsonDocument teamUpJSON = QJsonDocument::fromJson(response,&jsonError);
    if (jsonError.error != QJsonParseError::NoError){
        qDebug() << jsonError.errorString();
    }
    QList<QVariant> list = teamUpJSON.toVariant().toList();

    QList<QVariant>::ConstIterator it = list.constBegin();
    for ( ; it != list.constEnd(); ++it ) {
        QMap<QString, QVariant> map = it->toMap();
        std::string txt = "";
        txt.append(map["name"].toString().toStdString());
        txt.append(std::string(" 想要吃 "));
        txt.append(Restaurant::getNameByIndex(map["restaurant"].toInt()));
        ui->teamList->addItem(QString::fromStdString(txt));
    }

	QMap<QString, QVariant> map = list[0].toMap();
}

void TeamUp::addList(std::string username, int restaurant){
	manager = new QNetworkAccessManager();
	QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(managerAddListFinished(QNetworkReply*)));
	request.setUrl(QUrl((std::string("http://127.0.0.1:8080/?action=add") + "&username=" + username + "&restaurant=" + std::to_string(restaurant)).c_str()));
	manager->get(request);
}

void TeamUp::managerAddListFinished(QNetworkReply *reply){
	if (reply->error()) {
		qDebug() << reply->errorString();
		return;
	}
	if(reply->readAll() == "Added!"){
		QMessageBox::about(this,tr("消息框"),tr("新增成功"));
	}else{
		QMessageBox::warning(this,tr("消息框"),tr("新增失敗"));
	}
}
