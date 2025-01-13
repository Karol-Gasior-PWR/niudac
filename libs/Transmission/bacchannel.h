#ifndef BACCHANNEL_H
#define BACCHANNEL_H

#include "channel.h"
class BACChannel: public Channel
{
public:
    BACChannel(unsigned int seed, double transProbFromZero, double transProbFromOne);
public:
    virtual void applyInterference(std::vector<bool> & codeword) override;
    virtual Channel * clone() const  override;

private:
    double transProbFromZero;
    double transProbFromOne;
};

#endif // BACCHANNEL_H
