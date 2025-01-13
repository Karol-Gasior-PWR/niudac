#include "chartwindow.h"
#include "ui_chartwindow.h"

#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>

#include <QVBoxLayout>



chartWindow::chartWindow(std::vector<SimulationData> & simDataVector, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::chartWindow)
    , simDataVector{simDataVector}
{
    ui->setupUi(this);
    setupMenuButtons();

    ui->pBtn_leftMenu->setIcon(icon_leftArrow);
    ui->pBtn_rightMenu->setIcon(icon_rightArrow);

    simDataVectorChanged();    //updating series list
    setupChart();
}

chartWindow::~chartWindow()
{
    delete ui;
}

void chartWindow::closeEvent(QCloseEvent *event)
{
    deleteLater();
    event->accept();
}

void chartWindow::simDataVectorChanged()
{


    ui->listW_availableSeries->clear();


    for(auto & elem : simDataVector)
    {
        QString name = QString::fromStdString(elem.getName());

        QListWidgetItem *item = new QListWidgetItem(name);
        item->setData(Qt::UserRole, QVariant::fromValue(&elem));  // Przechowujemy wskaźnik do obiektu w elemencie
        ui->listW_availableSeries->addItem(item);
    }
}

void chartWindow::on_pBtn_leftMenu_clicked()
{
    leftMenuVisible = !leftMenuVisible;

    // Jeśli menu jest widoczne, zmniejszamy jego szerokość
    if (!leftMenuVisible) { //closing the menu
        animation_pBtn_leftMenu->setEndValue(0);
        ui->pBtn_leftMenu->setIcon(icon_rightArrow);
    } else {    //opening the menu
        animation_pBtn_leftMenu->setEndValue(200);
        ui->pBtn_leftMenu->setIcon(icon_leftArrow);
    }

    animation_pBtn_leftMenu->start();

}

void chartWindow::drawChart()
{
    chart.removeAllSeries();
    for(SimulationData * elem : simDataToDraw)
    {
        auto series = new QLineSeries;
        auto & data = elem->getSimData();

        qDebug() << "ptr org" << &(simDataVector[0]);
        qDebug() << "ptr elem" << elem;


        for(auto line : data)
        {
            series->append(line.getCodeDimension(), line.getNakCounter());
        }

        chart.addSeries(series);
        series->attachAxis(&axisX);
        series->attachAxis(&axisY);
    }
}

void chartWindow::on_pBtn_rightMenu_clicked()
{
    rightMenuVisible = !rightMenuVisible;

    // Jeśli menu jest widoczne, zmniejszamy jego szerokość
    if (!rightMenuVisible) { //closing the menu
        animation_pBtn_rightMenu->setEndValue(0);
        ui->pBtn_rightMenu->setIcon(icon_leftArrow);
    } else {    //opening the menu
        animation_pBtn_rightMenu->setEndValue(200);
        ui->pBtn_rightMenu->setIcon(icon_rightArrow);
    }
    animation_pBtn_rightMenu->start();

}

void chartWindow::setupMenuButtons()
{
    // Creating animation for left menu
    animation_pBtn_leftMenu = new QPropertyAnimation(ui->stackedW_left, "maximumWidth");
    animation_pBtn_leftMenu->setDuration(300);  // Czas trwania animacji
    animation_pBtn_leftMenu->setEasingCurve(QEasingCurve::InOutQuad);

    // Creating animation for right menu
    animation_pBtn_rightMenu = new QPropertyAnimation(ui->stackedW_right, "maximumWidth");
    animation_pBtn_rightMenu->setDuration(300);  // Czas trwania animacji
    animation_pBtn_rightMenu->setEasingCurve(QEasingCurve::InOutQuad);
}

void chartWindow::setupChart()
{

    //chart.legend()->hide();
    chart.setTitle("Poki co jeden");

    axisX.setTitleText("code dimension");

    axisY.setTitleText("Number of retransmitted bits");

    chart.addAxis(&axisX,Qt::AlignBottom);
    chart.addAxis(&axisY, Qt::AlignLeft);
    axisY.setMin(0.0);

    QChartView * view = new QChartView(&chart, this);
    view->setRenderHint(QPainter::Antialiasing);

    view->setVisible(true);
    chart.setVisible(true);


    // Tworzymy układ i dodajemy QChartView do objTest
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(view);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    // Ustawiamy layout dla objTest
    ui->widgetChart->setLayout(layout);

}


void chartWindow::on_actionLegend_Menu_triggered()
{
    if( ! leftMenuVisible)
        on_pBtn_leftMenu_clicked();

    ui->stackedW_left->setCurrentIndex(1);
}


void chartWindow::on_actionAxis_Menu_triggered()
{
    if( ! leftMenuVisible)
        on_pBtn_leftMenu_clicked();

    ui->stackedW_left->setCurrentIndex(0);
}


void chartWindow::on_actionData_Series_triggered()
{
    if( ! leftMenuVisible)
        on_pBtn_leftMenu_clicked();

    ui->stackedW_left->setCurrentIndex(2);
}


void chartWindow::on_listW_availableSeries_itemDoubleClicked(QListWidgetItem *item)
{
    /*
    SimulationData * selectedObject = item->data(Qt::UserRole).value<SimulationData*>();    //reading pointer to choosen object
    simDataToDraw.push_back(selectedObject);

    drawChart();
*/
}


void chartWindow::on_listW_availableSeries_itemSelectionChanged()
{

    QList<QListWidgetItem *> selectedItems = ui->listW_availableSeries->selectedItems();
    simDataToDraw.clear();
    simDataToDraw.resize(selectedItems.size());
    // Wyświetlanie zaznaczonych elementów w konsoli
    for (QListWidgetItem *item : selectedItems)
    {
        SimulationData * selectedObject = item->data(Qt::UserRole).value<SimulationData*>();    //reading pointer to choosen object
        simDataToDraw.push_back(selectedObject);
    }


    drawChart();
}

