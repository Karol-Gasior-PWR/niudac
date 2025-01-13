#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialogsimulationinfo.h"
#include "simulationdata.h"
#include <QMainWindow>




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_cBox_page_channel_currentIndexChanged(int index);
    void on_hSlider_channel_bsc_valueChanged(int value);
    void on_dSpinB_channel_bsc_valueChanged(double arg1);
    void on_dSpinB_channel_bac0_valueChanged(double arg1);
    void on_hSlider_channel_bac0_valueChanged(int value);
    void on_dSpinB_channel_bac1_valueChanged(double arg1);
    void on_hSlider_channel_bac1_valueChanged(int value);
    void on_cBox_page_coder_currentIndexChanged(int index);
    void on_actionView_list_triggered();
    void on_actionCalculation_list_triggered();
    void on_actionAuthors_triggered();
    void on_actionHelp_triggered();
    void on_actionCreate_triggered();
    void on_pBtn_model_source_clicked();
    void on_pBtn_model_encoder_clicked();
    void on_pBtn_model_channel_clicked();
    void on_pBtn_model_decoder_clicked();
    void on_pBtn_simulation_add_clicked();
    void on_actionNew_windows_triggered();
    void on_spinBox_minCodeDimension_valueChanged(int arg1);
    void on_spinBox_maxCodeDimension_valueChanged(int arg1);
    void on_pBtn_simulation_createCodeDimension_clicked();

    void on_dSpinB_channel_ge_toBad_valueChanged(double arg1);
    void on_hSlider_channel_ge_toBad_valueChanged(int value);

    void on_dSpinB_channel_ge_toGood_valueChanged(double arg1);

    void on_hSlider_channel_ge_toGood_valueChanged(int value);

    void on_dSpinB_channel_ge_trans_good_valueChanged(double arg1);

    void on_hSlider_channel_ge_trans_good_valueChanged(int value);

    void on_dSpinB_channel_ge_transBad_valueChanged(double arg1);

    void on_hSlider_channel_ge_transBad_valueChanged(int value);

public slots:
    void updateDataVectorsWidgets();
signals:
    void simDataVectorChanged();
private:
    Ui::MainWindow *ui;

    std::vector<SimulationData> simDataVector;
    std::vector<SimulationData> calculationVector;
    QString defaultPath;
    std::string filePath;
    DialogSimulationInfo * infoDialog;
};
#endif // MAINWINDOW_H
