#include "bacchannel.h"

BACChannel::BACChannel(unsigned int seed, double transProbFromZero, double transProbFromOne)
:
    Channel(seed),
    transProbFromZero{transProbFromZero},
    transProbFromOne{transProbFromOne}
{

}

void BACChannel::applyInterference(std::vector<bool> & codeword)
{
    for(int i=0; i < codeword.size(); ++i)
    {
        bool bit = codeword[i];
        double prop = distributor(generator);
        double transProb;

        //czy szybciej nie bylo by dokonac tranzycji bezposrednio w if else?
        if(bit) //if received bit equal 1
            transProb = transProbFromOne;
        else
            transProb = transProbFromZero;

        if(prop < transProb)
            codeword[i] = ! codeword[i];
    }
}

Channel *BACChannel::clone() const
{
    return new BACChannel{*this};
}
