#ifndef EQUIPMESSAGEDIALOG_H
#define EQUIPMESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class EquipMessageDialog;
}

class EquipMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EquipMessageDialog(QWidget *parent = 0);
    ~EquipMessageDialog();

private:
    Ui::EquipMessageDialog *ui;
};

#endif // EQUIPMESSAGEDIALOG_H
