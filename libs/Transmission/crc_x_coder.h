#ifndef CRC_X_CODER_H
#define CRC_X_CODER_H

#include "coder.h"
#include <cstdint>
#include <type_traits>

//bity w wektorze sa ustawione od najwiecej do najmniej znaczacego, [0] - najbardziej znaczacy

// Specjalizacja dla wybranych typów całkowitych
template <typename polyT>
class CRC_X_Coder: public Coder
{

public:
    CRC_X_Coder(const polyT polynomial);

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
    static constexpr int controlBitsLength = sizeof(polyT) * 8;// = 8 dla uint8_t
    static constexpr polyT mostImportantBit = (static_cast<polyT> (1u)) << ((sizeof(polyT)*8)-1) ; //= 0x80 dla uint8_t
    const polyT polynomial;
};


#endif // CRC_X_CODER_H
