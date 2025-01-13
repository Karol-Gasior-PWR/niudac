#ifndef CALCULATIONTHREAD_H
#define CALCULATIONTHREAD_H

#include <QObject>
#include <QThread>

#include <vector>
#include <memory>

#include "simulationdata.h"


class CalculationThread : public QThread
{
    Q_OBJECT

public:
    CalculationThread(std::shared_ptr<Channel> channel,
                      std::shared_ptr<Coder> coder,
                      std::string filePath,
                      std::pair<int,int>range,
                      std::vector<SimulationData> & simDataVector,
                      std::string name,
                      QObject *parent = nullptr);
protected:
    void run() override; // Przeciążenie metody run, gdzie będą wykonywane obliczenia

signals:
    void progress(int value);   // Signal do aktualizacji paska postępu
    void finished();             // Signal, gdy obliczenia zakończą się

private:
    void performCalculations();  // Funkcja wykonująca obliczenia

private:
    std::shared_ptr<Channel> channel;
    std::shared_ptr<Coder> coder;
    std::string filePath;
    std::pair<int,int>range;
    std::vector<SimulationData> & simDataVector;
    std::string name;
};

#endif // CALCULATIONTHREAD_H
