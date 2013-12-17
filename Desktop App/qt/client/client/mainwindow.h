#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

#include <l1/result.h>
#include <l1/xarg.h>
#include <l1/str.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool FindNetwork();
    bool isConnected();
    
private slots:
    void on_pushButton_connect_clicked();
    void tbAddEquipement();

private:
    QUdpSocket *udpSocket;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
