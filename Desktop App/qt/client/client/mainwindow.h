#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QFileDialog>

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
    bool findNetwork();
    bool isConnected();
    bool findArduino();
    
private slots:
    //auto-connect
    void on_pushButton_connect_clicked();
    void on_pushButton_findArduino_clicked();
    //menu
    void actionSauvegarder_sous();
    void actionOuvrir();
    //toolbar
    void tbAddEquipement();
    void tbRearrange();
    //autres
    void on_findArduinoResponse();

private:
    QUdpSocket *udpSocket;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
