#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <string>
#include <restaurant.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void setTitle(std::string title);
    void setName(std::string name);
    void setInfo(Restaurant::RestaurantContainer RestaurantInfo);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
	void on_teamUpBtn_clicked();

private:
	QString InputName();
    Ui::Dialog *ui;
    Dialog *dialog;
};

#endif // DIALOG_H
