#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include "simulationdata.h"
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QChart>
#include <QListWidget>
#include <qvalueaxis.h>

namespace Ui {
class chartWindow;
}

class chartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit chartWindow(std::vector<SimulationData> & simDataVector, QWidget *parent = nullptr);
    ~chartWindow();

    void closeEvent(QCloseEvent *event) override;
public slots:
        void simDataVectorChanged();
private slots:
    void on_pBtn_leftMenu_clicked();
    void on_pBtn_rightMenu_clicked();
    void on_listW_availableSeries_itemDoubleClicked(QListWidgetItem *item);
    void on_listW_availableSeries_itemSelectionChanged();



    void on_cBox_yAxis_currentIndexChanged(int index);

    void on_sBox_y_start_valueChanged(int arg1);

    void on_sBox_y_stop_valueChanged(int arg1);

    void on_sBox_y_scale_valueChanged(int arg1);

    void on_sBox_x_start_valueChanged(int arg1);

    void on_sBox_x_stop_valueChanged(int arg1);

private:
    void setupMenuButtons();
    void setupChart();
    void setupMenus();

    void drawChart();
private:
    Ui::chartWindow *ui;
    std::vector<SimulationData> & simDataVector;
    std::vector<SimulationData *>  simDataToDraw;

    QPropertyAnimation * animation_pBtn_leftMenu;
    QPropertyAnimation * animation_pBtn_rightMenu;
    QIcon icon_leftArrow{"resources/icons/arrow_left.png"};
    QIcon icon_rightArrow{"resources/icons/arrow_right.png"};
    TransmissionStruct::counterType (TransmissionStruct::*func_ptr)() const;    //pointer to func which, will get simulation axis Y data from data struct


    bool rightMenuVisible;
    bool leftMenuVisible;

    QChart chart;
    QValueAxis axisY;
    QValueAxis axisX;
};

#endif // CHARTWINDOW_H
