#ifndef PARITYCODER_H
#define PARITYCODER_H

#include "coder.h"
class ParityCoder : public Coder
{
public:
    enum class ParityMode;
public:
    ParityCoder(ParityMode parity);

    virtual std::vector<bool> encode(const std::vector<bool> & informationSequence) override;
    virtual std::vector<bool> decode(const std::vector<bool> & codeword ) override;
    virtual bool isValid(const std::vector<bool> & codeword) const noexcept override;
    virtual unsigned int getControlBitsNumber(unsigned int codeDimension) const override;
    virtual Coder * clone() const override;

private:
    const ParityMode parity;
};


enum class ParityCoder::ParityMode
{
    even,
    odd
};
#endif // PARITYCODER_H
