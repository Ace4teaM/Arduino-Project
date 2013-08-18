#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork>

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
    
private slots:
    void on_pushButton_connect_clicked();

private:
    QUdpSocket *udpSocket;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
