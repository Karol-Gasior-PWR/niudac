#ifndef GECHANNEL_H
#define GECHANNEL_H

#include <channel.h>

class GEChannel : public Channel
{
public:
    GEChannel(unsigned int seed, double transProbabilityInBadState, double transProbabilityInGoodState, std::pair<double, double> stateTransProb);
    virtual void applyInterference(std::vector<bool> & codeword) override;
    virtual Channel * clone() const  override;
private:
    inline void noiseOnChannelState();
    inline void noiseOnCodeword(bool & bit);
private:
    enum State : bool{ BAD = 0, GOOD = 1 };
    State state = GOOD;
    std::pair<double, double> stateTransProb;   //first =? from Good to Bad, second from bad to good
    double transProbabilityInBadState;
    double transProbabilityInGoodState;


};

#endif // GECHANNEL_H
