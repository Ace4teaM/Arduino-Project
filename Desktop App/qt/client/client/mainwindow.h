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
    bool FindNetwork();
    bool isConnected();
    
private slots:
    //auto slot connect
    void on_pushButton_connect_clicked();
    void on_btnSaveConfig_clicked();
    void on_btnLoadConfig_clicked();
    //menu
    void on_actionSauvegarder_sous_clicked();
    //toolbar
    void tbAddEquipement();
    void tbRearrange();

private:
    QUdpSocket *udpSocket;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
