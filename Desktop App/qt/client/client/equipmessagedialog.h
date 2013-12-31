#ifndef EQUIPMESSAGEDIALOG_H
#define EQUIPMESSAGEDIALOG_H

#include <QDialog>
#include "cominterface.h"
#include "app/application.h"
#include "model/Equipment.h"

extern Application* app;

namespace Ui {
class EquipMessageDialog;
}

class EquipMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EquipMessageDialog(Equipment & equipment, QWidget *parent = 0);
    ~EquipMessageDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EquipMessageDialog *ui;
    Equipment * equipment;
};

#endif // EQUIPMESSAGEDIALOG_H
