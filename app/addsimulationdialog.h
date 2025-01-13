#ifndef ADDSIMULATIONDIALOG_H
#define ADDSIMULATIONDIALOG_H

#include <QDialog>
#include <QPushButton>
namespace Ui {
class AddSimulationDialog;
}

class AddSimulationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSimulationDialog(QWidget *parent, QString * name, std::pair<uint,uint> * simRange, bool * isAccepted);
    ~AddSimulationDialog();

private slots:


    void on_spinBox_max_valueChanged(int arg1);

    void on_spinBox_min_valueChanged(int arg1);

    void on_AddSimulationDialog_accepted();

    void on_AddSimulationDialog_rejected();



    void on_lineEdit_editingFinished();

private:
    Ui::AddSimulationDialog *ui;
    QString * name;
    std::pair<uint,uint> * simRange;
    bool * isAccepted;
};

#endif // ADDSIMULATIONDIALOG_H
