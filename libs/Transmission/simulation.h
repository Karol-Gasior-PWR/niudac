#ifndef SIMULATION_H
#define SIMULATION_H


#include "channel.h"
#include "coder.h"
#include "filehandler.h"
#include "transmissionstruct.h"

#include <qelapsedtimer.h>
#include <qobjectdefs.h>




class Simulation
{
public:
    Simulation();
    void setSimulationData(std::string path);
    void setCoder(std::shared_ptr<Coder> coder);
    void setChannel( std::shared_ptr<Channel> channel);
    void simulate(unsigned int startCodeDimension, unsigned int stopCodeDimension);
    const std::vector<TransmissionStruct> & getData();
    qint64 getCalculationTime();
private:
    TransmissionStruct simulationStep(unsigned int codeDimension);
    std::vector<TransmissionStruct> simulationData;
    FileHandler fileHandler;
    qint64 calculationTime;
    std::shared_ptr<Coder> coder;
    std::shared_ptr<Channel> channel;

};

#endif // SIMULATION_H


