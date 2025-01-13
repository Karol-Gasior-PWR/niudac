#ifndef DIALOGSIMULATIONINFO_H
#define DIALOGSIMULATIONINFO_H

#include <QDialog>
#include <QTimer>
#include <QElapsedTimer>
#include <QMovie>

namespace Ui {
class DialogSimulationInfo;
}

class DialogSimulationInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSimulationInfo(QWidget *parent = nullptr);
    ~DialogSimulationInfo();

public slots:
    void enable();
private slots:
    void updateTimeLabel();
private:
    Ui::DialogSimulationInfo *ui;
    QElapsedTimer elapsedTimer;
    QTimer timer;
    QMovie duckMovie;
};

#endif // DIALOGSIMULATIONINFO_H
