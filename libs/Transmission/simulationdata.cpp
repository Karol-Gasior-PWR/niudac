#include "simulationdata.h"

SimulationData::SimulationData() {}

std::shared_ptr<Coder> SimulationData::getCoder() const
{
    return coder;
}

void SimulationData::setCoder(const std::shared_ptr<Coder> &newCoder)
{
    coder = newCoder;
}

std::shared_ptr<Channel> SimulationData::getChannel() const
{
    return channel;
}

void SimulationData::setChannel(const std::shared_ptr<Channel> &newChannel)
{
    channel = newChannel;
}

std::string SimulationData::getName() const
{
    return name;
}

void SimulationData::setName(const std::string &newName)
{
    name = newName;
}

std::string SimulationData::getSource_path() const
{
    return source_path;
}

void SimulationData::setSource_path(const std::string &newSource_path)
{
    source_path = newSource_path;   //kopiowanie danych
}

std::vector<TransmissionStruct> & SimulationData::getSimData()
{
    return simData;
}

void SimulationData::setSimData(const std::vector<TransmissionStruct> &newSimData)
{
    simData = newSimData;
}
