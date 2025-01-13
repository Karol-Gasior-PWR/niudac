#ifndef TRANSMISSIONSTRUCT_H
#define TRANSMISSIONSTRUCT_H


#include <string>

struct TransmissionStruct {
public:
    using counterType = long long;

    TransmissionStruct() = default;
    TransmissionStruct(counterType codeDimension,
                       counterType controlBitsNumber,
                       counterType wordsGivenToSend,
                       counterType totalSendedCodewords,
                       counterType nakCounter,
                       counterType ackCounter,
                       counterType retransmissionCounter,
                       counterType failedTransmissionCounter,
                       counterType wrongDetectedFalseCodewords,
                       counterType wrongDetectedPositiveCodewords,
                       counterType correctSendedCodewords);

public:
    operator std::string() const;

    counterType getReTransmittedBitsNumber() const;

    counterType getCodeDimension() const;
    void setCodeDimension(counterType newCodeDimension);
    counterType getControlBitsNumber() const;
    void setControlBitsNumber(counterType newControlBitsNumber);
    counterType getWordsGivenToSend() const;
    void setWordsGivenToSend(counterType newOrdsGivenToSend);
    counterType getTotalSendedCodewords() const;
    void setTotalSendedCodewords(counterType newTotalSendedCodewords);
    counterType getNakCounter() const;
    void setNakCounter(counterType newNakCounter);
    counterType getAckCounter() const;
    void setAckCounter(counterType newAckCounter);
    counterType getRetransmissionCounter() const;
    void setRetransmissionCounter(counterType newRetransmissionCounter);
    counterType getFailedTransmissionCounter() const;
    void setFailedTransmissionCounter(counterType newFailedTransmissionCounter);
    counterType getWrongDetectedFalseCodewords() const;
    void setWrongDetectedFalseCodewords(counterType newWrongDetectedFalseCodewords);
    counterType getWrongDetectedPositiveCodewords() const;
    void setWrongDetectedPositiveCodewords(counterType newWrongDetectedPositiveCodewords);
    counterType getCorrectSendedCodewords() const;
    void setCorrectSendedCodewords(counterType newCorrectSendedCodewords);

private:
    counterType codeDimension = 0;
    counterType controlBitsNumber = 0;
    counterType wordsGivenToSend = 0;
    counterType totalSendedCodewords= 0;    //all sended codewords, count retransmitted codewords
    counterType nakCounter = 0;
    counterType ackCounter = 0;
    counterType retransmissionCounter = 0;
    counterType failedTransmissionCounter = 0;
    counterType wrongDetectedFalseCodewords= 0; //corrupted information inside codeword detected as UNcorrupted
    counterType wrongDetectedPositiveCodewords= 0; //uncorrupted information inside codeword detected as corrupted
    counterType correctSendedCodewords = 0;



};


#endif // TRANSMISSIONSTRUCT_H
