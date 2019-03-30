#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_eatBtn_clicked();

    void on_teamupBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
