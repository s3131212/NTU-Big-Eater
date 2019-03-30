#include "dialog.h"
#include "ui_dialog.h"
#include "string"
#include "restaurant.h"
#include <QInputDialog>
#include "teamup.h"
#include "QDebug"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
    delete dialog;
}

void Dialog::setTitle(std::string title){
    Dialog::setWindowTitle(QString::fromUtf8(title.c_str()));
}

void Dialog::setName(std::string name){
    ui->restaurantName->setText(QString::fromStdString("<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">" + name + "</span></p></body></html>"));
}

void Dialog::setInfo(Restaurant::RestaurantContainer RestaurantInfo){
    std::string BudgetString[Restaurant::BUDGET_OPTIONS_NUM + 1];
    std::string TypeString[Restaurant::TYPE_OPTIONS_NUM + 1];
    TypeString[1] = "速食"; TypeString[2] = "自助"; TypeString[3] = "台式"; TypeString[4] = "義式"; TypeString[5] = "美式";
    TypeString[6] = "港式"; TypeString[7] = "日式"; TypeString[8] = "泰式"; TypeString[9] = "其他（小點心)"; TypeString[10] = "甜點";
    TypeString[11] = "冰品"; TypeString[12] = "飲料"; TypeString[13] = "咖啡廳"; TypeString[14] = "複合式";
    BudgetString[1] = "1 ~ 150 元"; BudgetString[2] = "150 ~ 250 元";  BudgetString[3] = "250 ~ 500 元";  BudgetString[4] = "500 元以上";

    std::string info = "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt;\">";
    info.append(std::string("地址：") + RestaurantInfo.address);
    info.append(std::string("<br />價位") +BudgetString[RestaurantInfo.budget]);

    ui->restaurantInfo->setText(QString::fromStdString(info));
}

void Dialog::on_pushButton_clicked()
{
    Dialog::close();
}

void Dialog::on_teamUpBtn_clicked()
{
	TeamUp *teamup = new TeamUp(this);
	QString temp = Dialog::InputName();
	std::string username = temp.toStdString();
	if(username != ""){
		teamup->addList(username, Restaurant::currentIndex);
	}
}

QString Dialog::InputName(){
	bool ok;
	QString text = QInputDialog::getText(this,tr(""),tr("請輸入姓名："),QLineEdit::Normal, "",&ok);
	if(ok && text.isEmpty()){
		QMessageBox::warning(this,tr("消息框"),tr("姓名不可空白"));
	}
	return text;
}
