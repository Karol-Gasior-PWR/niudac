#include "gechannel.h"

GEChannel::GEChannel(unsigned int seed
                     , double transProbabilityInBadState
                     , double transProbabilityInGoodState
                     , std::pair<double, double> stateTransProb)
:
    Channel{seed},
    transProbabilityInBadState{transProbabilityInBadState},
    transProbabilityInGoodState{transProbabilityInGoodState},
    stateTransProb{stateTransProb}
{

}

void GEChannel::applyInterference(std::vector<bool> & codeword)
{
    noiseOnChannelState();  //noise on channel state once per codeword
    for(int i=0; i < codeword.size(); ++i)
    {
        //noiseOnChannelState();    //noise on channel model on every bit

        //noise on one bit of the codeword
        double prop = distributor(generator);
        if(state == GOOD)
        {
            if(prop < transProbabilityInGoodState)
                codeword[i] = ! codeword[i];
        }
        else //state is BAD
        {
            if(prop < transProbabilityInBadState)
                codeword[i] = ! codeword[i];
        }

    }
}

Channel *GEChannel::clone() const
{
    return new GEChannel{*this};
}

void GEChannel::noiseOnChannelState()
{
    double propStateChange = distributor(generator);

    if(state == GOOD)   //channel state changing from good to bad
    {
        if(propStateChange < stateTransProb.first)
            state = BAD;
    }
    else    //from bad to good
    {
        if(propStateChange < stateTransProb.second)
            state = GOOD;
    }
}

void GEChannel::noiseOnCodeword(bool & bit)
{

    double prop = distributor(generator);

    if(state == GOOD)
    {
        if(prop < transProbabilityInGoodState)
            bit = ! bit;
    }
    else //state is BAD
    {
        if(prop < transProbabilityInBadState)
            bit = ! bit;
    }
}
