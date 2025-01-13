#include "crc_x_coder.h"
#include <vector>


using namespace std;

template <typename polyT>
CRC_X_Coder<polyT>::CRC_X_Coder(const polyT polynomial)
    :
    polynomial{polynomial}
{}
template <typename polyT>
std::vector<bool> CRC_X_Coder<polyT>::encode(const std::vector<bool> &informationSequence)
{
    vector<bool> codeword;
    auto crc = calculateCRC(informationSequence);

    codeword.reserve(informationSequence.size() + crc.size());
    codeword = informationSequence;

    std::copy(crc.begin(), crc.end(), std::back_inserter(codeword));

    return codeword;
}
template <typename polyT>
std::vector<bool> CRC_X_Coder<polyT>::decode(const std::vector<bool> & codeword)
{
    auto information{codeword};
    //if (information.size() >= controlBitsLength)
    {
        information.erase(information.end() - controlBitsLength, information.end());
    }
    return information;
}
template <typename polyT>
bool CRC_X_Coder<polyT>::isValid(const std::vector<bool> &codeword) const noexcept
{
    //auto crc  = extractControlBits(codeword);
    //auto info = extractInformationSequence(codeword)
    return extractControlBits(codeword) == calculateCRC(extractInformationSequence(codeword));;
}
template <typename polyT>
unsigned int CRC_X_Coder<polyT>::getControlBitsNumber(unsigned int codeDimension) const
{
    return controlBitsLength;
}
template <typename polyT>
Coder *CRC_X_Coder<polyT>::clone() const
{
    return new CRC_X_Coder<polyT>{*this};
}
//*********************************************************************************************************************
template <typename polyT>
std::vector<bool> CRC_X_Coder<polyT>::calculateCRC(const std::vector<bool> & info) const
{
    polyT crcReg = 0x00;  //

    // Dla każdego bitu w danych
    for (auto bit : info) {
        // Sprawdzamy, czy najwyższy bit CRC wynosi 1
        if (bit)
        {
            crcReg = (crcReg << 1) ^ polynomial;  // Jeśli tak, wykonujemy XOR z polinomem
        } else {
            crcReg <<= 1;  // W przeciwnym razie tylko przesuwamy CRC
        }
    }

    vector<bool> crc;
    for(int i=0; i<controlBitsLength; ++i)
    {
        crc.push_back( crcReg & mostImportantBit);
        crcReg = crcReg << 1;
    }

    return crc;
}
template <typename polyT>
std::vector<bool> CRC_X_Coder<polyT>::extractInformationSequence(const std::vector<bool> & codeword) const
{
    return vector<bool>{codeword.cbegin(), codeword.cend() - controlBitsLength};
}
template <typename polyT>
std::vector<bool> CRC_X_Coder<polyT>::extractControlBits(const std::vector<bool> & codeword) const
{
    return vector<bool>{codeword.cend() - controlBitsLength, codeword.cend()};
}


// Instancjowanie szablonu dla wybranych typów
template class CRC_X_Coder<uint8_t>;
template class CRC_X_Coder<uint16_t>;
template class CRC_X_Coder<uint32_t>;
template class CRC_X_Coder<uint64_t>;
