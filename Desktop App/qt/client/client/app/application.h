#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QClipboard>

#include "result.h"
#include "database.h"
#include "qassoclist.h"

#include <QTableWidget>
#include <QListWidget>
#include <QString>
#include <QDir>
#include <QMessageBox>

class Application : public QObject
{
    Q_OBJECT

public:

    //général
    Application(const QApplication* app );
    bool initialise(QWidget* mainWnd);
    const QApplication* app;
    void printResult(Result* pResult=0,QWidget* parent=0);
    void printMessage(const QString msg,QWidget* parent=0);

    //membres
    QWidget* wnd;

    //paths
    QString path;//chemin de base vers l'application
    QString configFileName;
};

#endif // APPLICATION_H
