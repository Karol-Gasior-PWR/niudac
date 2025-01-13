#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include "channel.h"
#include "coder.h"
#include "transmissionstruct.h"
#include <memory>

class SimulationData
{
public:
    SimulationData();


    std::shared_ptr<Coder> getCoder() const;
    void setCoder(const std::shared_ptr<Coder> &newCoder);
    std::shared_ptr<Channel> getChannel() const;
    void setChannel(const std::shared_ptr<Channel> &newChannel);
    std::string getName() const;
    void setName(const std::string &newName);
    std::string getSource_path() const;
    void setSource_path(const std::string &newSource_path);


    std::vector<TransmissionStruct> & getSimData();
    void setSimData(const std::vector<TransmissionStruct> & newSimData);

private:
    std::shared_ptr<Coder>  coder;
    std::shared_ptr<Channel> channel;
    std::string name;
    std::string source_path;
    std::pair<unsigned int,unsigned int> informationSequenceRange();
    std::vector<TransmissionStruct> simData;

};

#endif // SIMULATIONDATA_H


