#ifndef GECHANNEL_H
#define GECHANNEL_H

#include <channel.h>


class GEChannel : public Channel
{
public:
    GEChannel();
    virtual std::vector<bool> simulateInterference(std::vector<bool> & codeword) override;
    virtual void applyInterference(std::vector<bool> & codeword) override;
    virtual Channel * clone() const  override;
};

#endif // GECHANNEL_H
