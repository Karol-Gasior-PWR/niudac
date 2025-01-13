#ifndef CODEWORD_H
#define CODEWORD_H

#include <vector>
#include <string>

/*  Nie da sie oddzielic bitow informacji i kontroli na dwa rozne wektory bo mamy kod hamminga,
 *  oraz channel with memory. Wiec rozdzielenie ich wymagalo by aby kanal czytal bity w okreslonej
 *  kolejnosci. A gdy oba wektory sa razem to zadanie tylko i wylacznie codera.
 *
 *
 *
 */
class Codeword
{
public:
    /**
     * @brief Codeword constructs a new codeword
     * @param codeword contains bits of the codeword
     * @param codeDimension specifies, how many begining bits are informations bits
     */
    Codeword(const std::vector<bool> & codeword) noexcept;
    /**
     * @brief Codeword
     * @param orginal codeword which will be copied
     */
    Codeword(const Codeword &orginal) noexcept;
    Codeword & operator= (const Codeword & orginal) noexcept(false);
    bool operator==(const Codeword & codeword) const noexcept;
    operator std::string() const;
//=================================================================================================
    /**
     * @brief change changes the actual codeword (information and control bits) to *codeword*
     * @param codeword
     * @return reference to actual Codeword object
     */
    Codeword & change(const std::vector<bool> & codeword) noexcept(false);
    /**
     * @brief getCodeword return a vector containing codeword bits
     * @return
     */
    const std::vector<bool> & getCodeword() const;
    /**
     * @brief getCodeLength return number of information and control bits
     * @return
     */
    size_t getCodeLength() const noexcept;
    /**
     * @brief operator []   return a reference to bit with index *index*
     * @param index - works indentical to all indexes from std
     * @return
     */
    std::_Bit_reference operator[](size_t index) noexcept(false);
//=================================================================================================
private:
    /**
     * @brief codeword contains information bits as bool
     */
    std::vector<bool> codeword;             //contains encoded word
    /**
     * @brief codeDimension specifies how many beginig bits are information bits
     */
    unsigned int codeDimension;

};



#endif // CODEWORD_H
