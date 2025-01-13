#include "crc_8_coder.h"

using namespace std;


CRC_8_Coder::CRC_8_Coder(const uint8_t polynomial)
:
    polynomial{polynomial}
{}

std::vector<bool> CRC_8_Coder::encode(const std::vector<bool> &informationSequence)
{
    vector<bool> codeword;
    auto crc = calculateCRC(informationSequence);

    codeword.reserve(informationSequence.size() + crc.size());
    codeword = informationSequence;

    std::copy(crc.begin(), crc.end(), std::back_inserter(codeword));

    return codeword;
}

std::vector<bool> CRC_8_Coder::decode(const std::vector<bool> & codeword)
{
    auto information{codeword};
    //if (information.size() >= controlBitsLength)
    {
        information.erase(information.end() - controlBitsLength, information.end());
    }
    return information;
}

bool CRC_8_Coder::isValid(const std::vector<bool> &codeword) const noexcept
{
    //auto crc  = extractControlBits(codeword);
    //auto info = extractInformationSequence(codeword)
    return extractControlBits(codeword) == calculateCRC(extractInformationSequence(codeword));;
}

unsigned int CRC_8_Coder::getControlBitsNumber(unsigned int codeDimension) const
{
    return controlBitsLength;
}

Coder *CRC_8_Coder::clone() const
{
    return new CRC_8_Coder{*this};
}
//*********************************************************************************************************************
std::vector<bool> CRC_8_Coder::calculateCRC(const std::vector<bool> & info) const
{
    uint8_t crcReg = 0x00;  //

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
        crc.push_back( crcReg & 0x80);
        crcReg = crcReg << 1;
    }

    return crc;
}

std::vector<bool> CRC_8_Coder::extractInformationSequence(const std::vector<bool> & codeword) const
{
    return vector<bool>{codeword.cbegin(), codeword.cend() - controlBitsLength};
}

std::vector<bool> CRC_8_Coder::extractControlBits(const std::vector<bool> & codeword) const
{
    return vector<bool>{codeword.cend() - controlBitsLength, codeword.cend()};
}
