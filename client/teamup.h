#ifndef TEAMUP_H
#define TEAMUP_H

#include <QDialog>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

namespace Ui {
class TeamUp;
}

class TeamUp : public QDialog
{
    Q_OBJECT

public:
    explicit TeamUp(QWidget *parent = nullptr);
	void getList();
	void addList(std::string username, int restaurant);
    ~TeamUp();

private:
    Ui::TeamUp *ui;
    TeamUp *teamup;
    QNetworkAccessManager *manager;
    QNetworkRequest request;

private slots:
	void managerGetListFinished(QNetworkReply *reply);
	void managerAddListFinished(QNetworkReply *reply);
};

#endif // TEAMUP_H
