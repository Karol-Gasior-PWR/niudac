#include "codeword.h"
#include <stdexcept>
#include <stdexcept>

using namespace std;

Codeword::Codeword(const std::vector<bool>  & codeword) noexcept
    :
    codeword(codeword)
{
    //this->codeDimension = codeDimension;
    //this->codeword = std::vector<bool>(codeword);
}
//-------------------------------------------------------------------------------------------------
Codeword::Codeword(const Codeword & orginal) noexcept
{
    this->codeDimension = orginal.codeDimension;
    this->codeword = vector<bool>{orginal.codeword};
}
//-------------------------------------------------------------------------------------------------
Codeword &Codeword::operator=(const Codeword & orginal) noexcept(false)
{
    if(this != &orginal)
    {
        this->codeword = std::vector<bool>(codeword);;
    }

    return *this;
}
//-------------------------------------------------------------------------------------------------
bool Codeword::operator==(const Codeword &codeword) const noexcept
{
    if(this == & codeword)
        return true;

    if(this->getCodeLength() != codeword.getCodeLength())
        return false;

    if(this->codeword != codeword.getCodeword())
        return false;

    return true;
}

Codeword::operator std::string() const
{
    string str{"[ "};
    for(auto bit : codeword)
    {
        if(bit)
            str += "1";
        else
            str += "0";
    }
    str +=" ]";

    return str;
}
//=================================================================================================
Codeword & Codeword::change(const std::vector<bool> &codeword) noexcept(false)
{
    if(codeword.size() != this->codeword.size())
        throw std::invalid_argument("Code length doesn't match");
    else
        this->codeword = std::vector<bool>(codeword);

    return *this;
}
//-------------------------------------------------------------------------------------------------
/**
 * @brief Codeword::getCodeword
 * @return returns a codeword
 */
const std::vector<bool> & Codeword::getCodeword() const
{
    return  codeword;
}
//-------------------------------------------------------------------------------------------------
size_t Codeword::getCodeLength() const noexcept
{
    return codeword.size();
}
//-------------------------------------------------------------------------------------------------
_Bit_reference Codeword::operator [](size_t index)
{
    return codeword[index];
}
