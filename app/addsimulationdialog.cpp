#include "addsimulationdialog.h"
#include "ui_addsimulationdialog.h"

AddSimulationDialog::AddSimulationDialog(QWidget *parent, QString * name, std::pair<uint,uint> * simRange, bool * isAccepted)
    : QDialog(parent)
    , ui(new Ui::AddSimulationDialog),
    name{name},
    simRange{simRange},
    isAccepted{isAccepted}
{
    ui->setupUi(this);
    *isAccepted = false;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

AddSimulationDialog::~AddSimulationDialog()
{
    delete ui;
}

void AddSimulationDialog::on_spinBox_max_valueChanged(int arg1)
{
    ui->spinBox_min->setMaximum(arg1-1);
}


void AddSimulationDialog::on_spinBox_min_valueChanged(int arg1)
{
    ui->spinBox_max->setMinimum(arg1+1);
}


void AddSimulationDialog::on_AddSimulationDialog_accepted()
{
    *isAccepted = true;
    *name = ui->lineEdit->text();
    simRange->first = ui->spinBox_min->value();
    simRange->second = ui->spinBox_max->value();
}


void AddSimulationDialog::on_AddSimulationDialog_rejected()
{
    *isAccepted = false;
}

void AddSimulationDialog::on_lineEdit_editingFinished()
{
    QString txt = ui->lineEdit->text();
    txt = txt.trimmed();
    if(txt.isEmpty())
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    else
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

