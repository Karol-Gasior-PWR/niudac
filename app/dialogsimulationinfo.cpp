#include "dialogsimulationinfo.h"
#include "ui_dialogsimulationinfo.h"



DialogSimulationInfo::DialogSimulationInfo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogSimulationInfo)
    , timer{this}
    ,duckMovie{"resources/gifs/duck2.gif"}
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    elapsedTimer.start();
    connect(&timer, &QTimer::timeout, this, &DialogSimulationInfo::updateTimeLabel);
    timer.start(1000);
    updateTimeLabel();


    // Ustaw film na QLabel
    ui->label_gif->setMovie(&duckMovie);

    // Rozpocznij odtwarzanie animacji
    duckMovie.start();
    ui->label_gif->show();

    if (!duckMovie.isValid()) {
        qDebug() << "Nie udało się załadować pliku GIF!";
        ; // Zakończ aplikację, jeśli GIF się nie załadował
    }

    this->setWindowTitle("Tancz kaczuszko, tancz");
}

DialogSimulationInfo::~DialogSimulationInfo()
{
    delete ui;
}

void DialogSimulationInfo::enable()
{
    duckMovie.stop();
    timer.stop();
    ui->buttonBox->setEnabled(true);
}

void DialogSimulationInfo::updateTimeLabel()
{
    // Obliczenie czasu od startu aplikacji
    qint64 elapsedSecs = elapsedTimer.elapsed() / 1000; // elapsed time in sec
    int hours = elapsedSecs / 3600;
    int minutes = (elapsedSecs % 3600) / 60;
    int seconds = elapsedSecs % 60;

    // Ustawienie tekstu na QLabel w formacie "hh:mm:ss"
    ui->label_time->setText(QString("Czas od uruchomienia: %1:%2:%3")
                           .arg(hours, 2, 10, QChar('0'))
                           .arg(minutes, 2, 10, QChar('0'))
                           .arg(seconds, 2, 10, QChar('0')));

}
