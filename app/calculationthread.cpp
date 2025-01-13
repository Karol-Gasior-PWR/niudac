#include "calculationthread.h"
#include "threadmanager.h"


CalculationThread::CalculationThread(std::shared_ptr<Channel> channel,
                  std::shared_ptr<Coder> coder,
                  std::string filePath,
                  std::pair<int,int>range,
                  std::vector<SimulationData> & simDataVector,
                  std::string name,
                  QObject *parent)
:
    QThread{parent},
    channel{channel},
    coder{coder},
    filePath{filePath},
    range{range},
    simDataVector{simDataVector},
    name{name}
{

}

void CalculationThread::run()
{
    performCalculations();
    emit finished();  // Emitujemy sygnał po zakończeniu obliczeń

    deleteLater();//deleting the info after calculations
}

void CalculationThread::performCalculations()
{

    //3 stworzenie nowej sym

    SimulationData simData{};
    simData.setChannel(channel);
    simData.setCoder(coder);
    simData.setName(name);
    simData.setSource_path(filePath);

    std::vector<TransmissionStruct> transmissionData;

    transmissionData = func(coder.get(), channel.get(),filePath, range);    //make simulation

    simData.setSimData(transmissionData);

    simDataVector.push_back(simData);
}
