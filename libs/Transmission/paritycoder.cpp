#include "paritycoder.h"
#include <stdexcept>

using namespace std;

//=================================================================================================
constexpr unsigned int parityBitsNumber = 1;
//=================================================================================================
ParityCoder::ParityCoder(ParityMode parity)
:
    parity(parity)
{

}
//=================================================================================================
//-------------------------------------------------------------------------------------------------
std::vector<bool> ParityCoder::encode(const std::vector<bool> & informationSequence)
{
    auto codeword{ informationSequence };

    if(informationSequence.size() == 0)
        throw std::invalid_argument("Sended an empty information sequence");

    unsigned int sum = 0;
    for(auto bit : informationSequence)
        sum += bit;

    sum = sum % 2;

    if(parity == ParityMode::even)
        codeword.push_back(sum);
    else
        codeword.push_back((sum + 1) % 2);

    return codeword;    //RVO should be applied
}
//-------------------------------------------------------------------------------------------------
std::vector<bool> ParityCoder::decode(const std::vector<bool> & codeword )
{
    auto information { codeword };
    information.pop_back();
    return information;
}
//-------------------------------------------------------------------------------------------------
bool ParityCoder::isValid(const std::vector<bool> & codeword) const noexcept
{

    unsigned int sum = 0;
    for(auto bit : codeword)
        sum += bit;

    sum = sum % 2;

    if(parity == ParityMode::even)
    {
        if(sum == 0)
            return true;
    }
    else if (parity == ParityMode::odd)
        if(sum == 1)
            return true;

    return false;
}
//-------------------------------------------------------------------------------------------------
unsigned int ParityCoder::getControlBitsNumber(unsigned int) const
{
    return parityBitsNumber;   //add always only one parity bit
}

Coder * ParityCoder::clone() const
{
    return new ParityCoder{*this};
}
