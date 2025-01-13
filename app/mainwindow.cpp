#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

#include "addsimulationdialog.h"
#include "bscchannel.h"
#include "calculationthread.h"
#include "chartwindow.h"
#include "csvexporter.h"
#include "dialogsimulationinfo.h"
#include "paritycoder.h"
#include "threadmanager.h"
#include "ui_mainwindow.h"

using namespace  std;

constexpr int seed = 0;
constexpr const char default_path[] = "resources/sources/romeo.txt";

enum class CoderTyp : int
{
    parity = 0,
    crc = 1
};
enum class ChannelTyp : int
{
    bsc = 0,
    bac,
    eliotGillber,
    burstError,
    markov
};



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    defaultPath = QCoreApplication::applicationDirPath()+"/"+::default_path;
    QFileInfo fileInfo(defaultPath);
    if (!fileInfo.exists() || !fileInfo.isFile()) {
        QMessageBox::critical(this, "Critical error", "Could not find default data file romeo.txt");
    }
    filePath = defaultPath.toStdString();


    ui->stackedW_channel->setCurrentIndex(ui->cBox_page_channel->currentIndex());
    ui->stackedW_coder->setCurrentIndex(ui->cBox_page_coder->currentIndex());
}
//---------------------------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_cBox_page_channel_currentIndexChanged(int index)
{
    ui->stackedW_channel->setCurrentIndex(index);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_hSlider_channel_bsc_valueChanged(int value)
{
    ui->dSpinB_channel_bsc->setValue(value);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_dSpinB_channel_bsc_valueChanged(double arg1)
{
    ui->hSlider_channel_bsc->setValue(arg1);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_dSpinB_channel_bac0_valueChanged(double arg1)
{
    ui->hSlider_channel_bac0->setValue(arg1);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_hSlider_channel_bac0_valueChanged(int value)
{
    ui->dSpinB_channel_bac0->setValue(value);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_dSpinB_channel_bac1_valueChanged(double arg1)
{
    ui->hSlider_channel_bac1->setValue(arg1);

}

void MainWindow::on_hSlider_channel_bac1_valueChanged(int value)
{
    ui->dSpinB_channel_bac1->setValue(value);

}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_cBox_page_coder_currentIndexChanged(int index)
{
    ui->stackedW_coder->setCurrentIndex(index);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_actionView_list_triggered()
{
    ui->stakcedW_main->setCurrentIndex(2);  //main model page
    ui->stackedW_sideMenu->setCurrentIndex(2);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_actionCalculation_list_triggered()
{
    ui->stakcedW_main->setCurrentIndex(2);  //main model page
    ui->stackedW_sideMenu->setCurrentIndex(4);   //calculation page
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_actionAuthors_triggered()
{
    ui->stakcedW_main->setCurrentIndex(0);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_actionHelp_triggered()
{
    ui->stakcedW_main->setCurrentIndex(1);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_actionCreate_triggered()
{
    ui->stakcedW_main->setCurrentIndex(2);
    ui->stackedW_sideMenu->setCurrentIndex(3);

}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_pBtn_model_source_clicked()
{
    QFileDialog fileDialog{this, "Transmission data", QCoreApplication::applicationDirPath()};
    QString choosenFilepath = fileDialog.getOpenFileName();
    if(! choosenFilepath.isEmpty())
        filePath = choosenFilepath.toStdString();

    //ui->stackedW_sideMenu->setCurrentIndex(3);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_pBtn_model_encoder_clicked()
{
        ui->stackedW_sideMenu->setCurrentIndex(1);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_pBtn_model_channel_clicked()
{
        ui->stackedW_sideMenu->setCurrentIndex(0);
}
//---------------------------------------------------------------------------------------------------------------------
void MainWindow::on_pBtn_model_decoder_clicked()
{
        ui->stackedW_sideMenu->setCurrentIndex(1);
}
//---------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pBtn_simulation_add_clicked()
{
    /*
    bool ok = true;
    QString simName;
    std::pair<uint,uint> range;
    auto diag = new AddSimulationDialog(this, &simName, &range, &ok);
    diag->exec();

    simName = simName.trimmed();
    if(!ok)
    {
        qDebug() << "canceled adding sim to calc stack";
        return;
    }
    else if (ok && simName.isEmpty()) {
        QMessageBox::warning(this, "Invalid name", "You have provided invalid simulation name, "
        "\nsimulation was not added to calculation stack");
        return;
    }
    */
    auto item = ui->listW_simulations->currentItem();
    if(item == nullptr)
    {
        QMessageBox::warning(this, "Export aborted", "No element was choosen to export.");
        return;
    }


    SimulationData * selectedObject = item->data(Qt::UserRole).value<SimulationData*>();    //reading pointer to choosen object


    QString choosenFilepath = QFileDialog::getSaveFileName(this,
                                                    "Zapisz plik",
                                                    "", // Początkowa ścieżka
                                                    "Pliki tekstowe (*.txt);;Wszystkie pliki (*.*)"); // Filtr plików
    //todo sprawdzic czy mozna utworzyc

    CSVExporter exporter{choosenFilepath, this, *selectedObject};
}

void MainWindow::on_actionNew_windows_triggered()
{
    chartWindow * win;
    win = new chartWindow{ simDataVector ,this};
    connect(this, &MainWindow::simDataVectorChanged, win, &chartWindow::simDataVectorChanged);
    win->show();
}

void MainWindow::on_spinBox_minCodeDimension_valueChanged(int arg1)
{
    ui->spinBox_maxCodeDimension->setMinimum(arg1+10);
}


void MainWindow::on_spinBox_maxCodeDimension_valueChanged(int arg1)
{
    ui->spinBox_minCodeDimension->setMaximum(arg1-10);
}


void MainWindow::on_pBtn_simulation_createCodeDimension_clicked()
{
    //check if the simulation name is appriopiate
    QString simName = ui->lineEdit_simName->text();
    simName = simName.trimmed();    //deleting white signs
    if(simName.isEmpty())
    {
        QMessageBox::critical(this, "Operation Aborted", "Provided simulation name \""+simName+"\" is incorrect",
                              QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    //making dialog to show calculation info and progres
    infoDialog = new DialogSimulationInfo{this};
    infoDialog->show();

    //1 making Coder
    shared_ptr<Coder> coder;
    CoderTyp coderTyp = static_cast<CoderTyp> (ui->cBox_page_coder->currentIndex());
    switch(coderTyp)
    {
    case CoderTyp::parity:
        if(ui->rBtn_parity_even->isChecked())
            coder = make_shared<ParityCoder>(ParityCoder::ParityMode::even);
        else
            coder = make_shared<ParityCoder>(ParityCoder::ParityMode::odd);
        break;

    case CoderTyp::crc:
        break;
    }
    //2 making Channel
    shared_ptr<Channel> channel;
    ChannelTyp channelTyp = static_cast<ChannelTyp>(ui->cBox_page_channel->currentIndex());
    switch(channelTyp)
    {
    case ChannelTyp::bsc:
        channel = make_shared<BSCChannel>(seed, ui->dSpinB_channel_bsc->value()/100);   //'/100' because it is in %, and channel is 0-1
        break;
    case ChannelTyp::bac:
        //channel = make_shared<BACChannel>(seed, ui->dSpinB_channel_bac0->value(), ///);
        break;
    case ChannelTyp::eliotGillber:
        break;
    case ChannelTyp::burstError:
        break;
    case ChannelTyp::markov:
        break;
    }

    //3 starting calculation
    std::pair<int,int> range {ui->spinBox_minCodeDimension->value(), ui->spinBox_maxCodeDimension->value()};
    string name = simName.toStdString();

    CalculationThread * calcThread = new CalculationThread{channel, coder, filePath, range, simDataVector, name, this};

    connect(calcThread, &CalculationThread::finished, this, &MainWindow::updateDataVectorsWidgets); //updating list with simulation data
    connect(calcThread, &CalculationThread::finished, infoDialog, &DialogSimulationInfo::enable); //enabling closing of calc window
    calcThread->start();
}

void MainWindow::updateDataVectorsWidgets()
{
    ui->listW_simulations->clear();

    for(auto & elem : simDataVector)
    {
        QString name = QString::fromStdString(elem.getName());

        QListWidgetItem *item = new QListWidgetItem(name);
        item->setData(Qt::UserRole, QVariant::fromValue(&elem));  // Przechowujemy wskaźnik do obiektu w elemencie
        ui->listW_simulations->addItem(item);
    }
    emit simDataVectorChanged();
}

