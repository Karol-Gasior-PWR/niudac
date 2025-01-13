#ifndef CHANNEL_H
#define CHANNEL_H

//std libraries
#include <random>
//Qt libraries

//Intern libraries





/**
 * @brief The Channel class is responsible for simulating an channel
 *
 *  - simulate interference on codeword
 *  -
 */


class Channel
{

//=====================================================================================================================
public:
    explicit Channel(unsigned int seed = 0);
    virtual ~ Channel() = default;
//=====================================================================================================================
public:
    void resetRandomEngine();
    virtual std::vector<bool> simulateInterference(std::vector<bool> & codeword) = 0;
    virtual void applyInterference(std::vector<bool> & codeword) = 0;
    virtual Channel * clone() const  = 0;
//=====================================================================================================================

//=====================================================================================================================
protected:
    mutable std::mt19937 generator;
    mutable std::uniform_real_distribution<> distributor;
    unsigned int seed;
};

#endif // CHANNEL_H
