#include "channel.h"


using namespace std;


Channel::Channel(unsigned int seed)
:

    distributor(0.0, 1.0)
{
    if(seed != 0)
    {
        this->seed = seed;
        generator = mt19937(seed);
    }
    else
    {
        this->seed = random_device{}();
        generator = mt19937{this->seed};
    }
}

void Channel::resetRandomEngine()
{
    generator = mt19937{seed};
}
//---------------------------------------------------------------------------------------------------------------------

//=====================================================================================================================


