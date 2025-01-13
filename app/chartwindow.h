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
    void on_actionLegend_Menu_triggered();
    void on_actionAxis_Menu_triggered();
    void on_actionData_Series_triggered();
    void on_listW_availableSeries_itemDoubleClicked(QListWidgetItem *item);
    void on_listW_availableSeries_itemSelectionChanged();

private:
    void setupMenuButtons();
    void setupChart();

    void drawChart();
private:
    Ui::chartWindow *ui;
    std::vector<SimulationData> & simDataVector;
    std::vector<SimulationData *>  simDataToDraw;

    QPropertyAnimation * animation_pBtn_leftMenu;
    QPropertyAnimation * animation_pBtn_rightMenu;
    QIcon icon_leftArrow{"resources/icons/arrow_left.png"};
    QIcon icon_rightArrow{"resources/icons/arrow_right.png"};

    bool rightMenuVisible = true;
    bool leftMenuVisible = true;

    QChart chart;
    QValueAxis axisY;
    QValueAxis axisX;
};

#endif // CHARTWINDOW_H
