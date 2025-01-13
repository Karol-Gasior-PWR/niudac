#ifndef CODER_H
#define CODER_H

#include <vector>

class Coder
{
public:
    Coder();
    virtual ~Coder() = default;

    virtual std::vector<bool> encode(const std::vector<bool> & informationSequence) = 0;
    virtual std::vector<bool> decode(const std::vector<bool> & codeword ) = 0;
    virtual bool isValid(const std::vector<bool> & codeword) const noexcept = 0 ;
    virtual unsigned int getControlBitsNumber(unsigned int codeDimension) const = 0;
    virtual Coder * clone() const =0;
};

#endif // CODER_H
