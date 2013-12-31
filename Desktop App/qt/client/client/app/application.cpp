#include "application.h"

/*--------------------------------------------------------------------------------
  Application
--------------------------------------------------------------------------------
*/
Application::Application(int & argc, char ** argv ) : QApplication(argc,argv)
{
    this->wnd = 0;
    //sauvegarde le repertoire de travail
    this->path = QDir::currentPath();
    //fichiers statiques
    this->configFileName = this->path+"/config.xml";

}

/*--------------------------------------------------------------------------------
  Methodes
--------------------------------------------------------------------------------*/

bool Application::initialise(QWidget* mainWnd){
    this->wnd = mainWnd;

    return true;
}

void Application::printResult(Result* pResult,QWidget* parent){

    if(pResult == 0)
        pResult = Result::getLast();

    printf("pResult=%p\n",pResult);

    if(pResult == 0)
        return;

    if(parent == 0)
        parent = this->wnd;

    printf("parent=%p\n",parent);

    if(parent == 0)
        return;

    //message box
    QMessageBox::critical(parent, *pResult->getMsg(), *pResult->getDesc());
}

/** @brief Affiche un message d'information */
void Application::printMessage(const QString msg,QWidget* parent){
    if(parent == 0)
        parent = this->wnd;

    //message box
    QMessageBox::information(parent, "Informations", msg);
}
