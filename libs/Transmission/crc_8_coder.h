#ifndef CRC_8_CODER_H
#define CRC_8_CODER_H

#include "coder.h"
#include <cstdint>


//bity w wektorze sa ustawione od najwiecej do najmniej znaczacego, [0] - najbardziej znaczacy

class CRC_8_Coder : public Coder
{
public:
    CRC_8_Coder(const uint8_t polynomial);

    virtual std::vector<bool> encode(const std::vector<bool> & informationSequence);
    virtual std::vector<bool> decode(const std::vector<bool> & codeword );
    virtual bool isValid(const std::vector<bool> & codeword) const noexcept;
    virtual unsigned int getControlBitsNumber(unsigned int codeDimension) const;
    virtual Coder * clone() const ;

private:
    std::vector<bool> calculateCRC(const std::vector<bool> & info) const;
    std::vector<bool> extractInformationSequence(const std::vector<bool> & codeword) const;
    std::vector<bool> extractControlBits(const std::vector<bool> & codeword) const;
private:
    static constexpr int controlBitsLength = 8;
    const uint8_t polynomial;
};

#endif // CRC_8_CODER_H
