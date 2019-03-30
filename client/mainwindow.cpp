#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDebug"
#include "restaurant.h"
#include "dialog.h"
#include "teamup.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->eatBtn->setAutoDefault(false);

    // Load restaurant data
    char filename[100] = "/home/allen/Desktop/project/project/table.csv";
    Restaurant::load_Csv(filename);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_eatBtn_clicked()
{
    // 想睡覺，有空再改好看一點
    bool type[Restaurant::TYPE_OPTIONS_NUM + 1] = {
        false,
        (ui->A1->checkState() ? true : false),
        (ui->A2->checkState() ? true : false),
        (ui->A3->checkState() ? true : false),
        (ui->A4->checkState() ? true : false),
        (ui->A5->checkState() ? true : false),
        (ui->A6->checkState() ? true : false),
        (ui->A7->checkState() ? true : false),
        (ui->A8->checkState() ? true : false),
        (ui->A9->checkState() ? true : false),
        (ui->A10->checkState() ? true : false),
        (ui->A11->checkState() ? true : false),
        (ui->A12->checkState() ? true : false),
        (ui->A13->checkState() ? true : false),
        (ui->A14->checkState() ? true : false)
    };
    bool budget[Restaurant::BUDGET_OPTIONS_NUM + 1] = {
        false,
        (ui->B1->checkState() ? true : false),
        (ui->B2->checkState() ? true : false),
        (ui->B3->checkState() ? true : false),
        (ui->B4->checkState() ? true : false)
    };

    bool place[Restaurant::PLACE_OPTIONS_NUM + 1] = {
        false,
        (ui->C1->checkState() ? true : false),
        (ui->C2->checkState() ? true : false),
        (ui->C3->checkState() ? true : false),
        (ui->C4->checkState() ? true : false),
        (ui->C5->checkState() ? true : false),
        (ui->C6->checkState() ? true : false)
    };

    int ans = Restaurant::findAvailable(type, budget, place);
    if(ans != -1){
        Dialog *dialog = new Dialog(this);
        dialog->setModal(true);
        dialog->setTitle("吃！");
        dialog->setName(Restaurant::getNameByIndex(ans));
        dialog->setInfo(Restaurant::getInfoByIndex(ans));
        dialog->show();
    }else{
        QMessageBox::about(this,tr("沒得吃 QQ"), tr("找不到餐廳資訊"));
    }
}

void MainWindow::on_teamupBtn_clicked()
{
    TeamUp *teamup = new TeamUp(this);
	  teamup->getList();
    teamup->setModal(true);
    teamup->show();
}
