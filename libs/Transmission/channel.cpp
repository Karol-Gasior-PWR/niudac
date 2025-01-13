#include "channel.h"


using namespace std;


Channel::Channel(unsigned int seed)
:

    distributor(0.0, 1.0)
{
    if(seed != 0)   //if seed ori=ovided by user
    {
        this->seed = seed;
        generator = mt19937(seed);
    }
    else    // user has not provided a seed
    {
        this->seed = random_device{}();
        generator = mt19937{this->seed};
    }
}

void Channel::resetRandomEngine()
{
    generator = mt19937{seed};
}

std::vector<bool> Channel::simulateInterference(std::vector<bool> &codeword)
{
    auto codewordWithNoise {codeword};
    applyInterference(codewordWithNoise);
    return codewordWithNoise;
}

//---------------------------------------------------------------------------------------------------------------------

//=====================================================================================================================


