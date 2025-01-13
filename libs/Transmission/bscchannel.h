#ifndef BSCCHANNEL_H
#define BSCCHANNEL_H

#include "channel.h"


class BSCChannel : public Channel
{
public:
    explicit BSCChannel(unsigned int seed, double atransitionPropability);  //transition probability 0-1
    std::vector<bool> simulateInterference(std::vector<bool> & codeword) override;
    void applyInterference(std::vector<bool> & codeword) override;
    Channel * clone() const override;
    double getTransitionPropability();
private:
    const double transitionPropability;
};

#endif // BSCCHANNEL_H
