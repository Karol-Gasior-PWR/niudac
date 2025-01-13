#include "bscchannel.h"

using namespace std;

BSCChannel::BSCChannel(unsigned int seed, double transitionPropability)
:
    Channel(seed),
    transitionPropability(transitionPropability)
{

}
//=====================================================================================================================


void BSCChannel::applyInterference(std::vector<bool> & codeword)
{
    for(int i=0; i < codeword.size(); ++i)
    {
        double prop = distributor(generator);
        if(prop < transitionPropability)
            codeword[i] = ! codeword[i];
    }
}

Channel *BSCChannel::clone() const
{
    return new BSCChannel{*this};
}

double BSCChannel::getTransitionPropability()
{
    return transitionPropability;
}





