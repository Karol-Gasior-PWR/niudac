#include "transmissionstruct.h"

TransmissionStruct::TransmissionStruct(TransmissionStruct::counterType codeDimension,
                                       TransmissionStruct::counterType controlBitsNumber,
                                       TransmissionStruct::counterType wordsGivenToSend,
                                       TransmissionStruct::counterType totalSendedCodewords,
                                       TransmissionStruct::counterType nakCounter,
                                       TransmissionStruct::counterType ackCounter,
                                       TransmissionStruct::counterType retransmissionCounter,
                                       TransmissionStruct::counterType failedTransmissionCounter,
                                       TransmissionStruct::counterType wrongDetectedFalseCodewords,
                                       TransmissionStruct::counterType wrongDetectedPositiveCodewords,
                                       TransmissionStruct::counterType correctSendedCodewords)
    : codeDimension(codeDimension),
    controlBitsNumber(controlBitsNumber),
    wordsGivenToSend(wordsGivenToSend),
    totalSendedCodewords(totalSendedCodewords),
    nakCounter(nakCounter),
    ackCounter(ackCounter),
    retransmissionCounter(retransmissionCounter),
    failedTransmissionCounter(failedTransmissionCounter),
    wrongDetectedFalseCodewords(wrongDetectedFalseCodewords),
    wrongDetectedPositiveCodewords(wrongDetectedPositiveCodewords),
    correctSendedCodewords(correctSendedCodewords)
{

}


TransmissionStruct::operator std::string() const
{
    std::string str{""};
    /*
    str+= "Words: ";
    str += std::to_string(wordCounter);
    str+= ", Nak: ";
    str += std::to_string(nakCounter);
    str+= ", codeDimension: ";
    str += std::to_string(codeDimension);
    str+= ", wrongWord: ";
    str += std::to_string(wrongWordCounter);
*/
    return str;
}

TransmissionStruct::counterType TransmissionStruct::getCodeDimension() const
{
    return codeDimension;
}

void TransmissionStruct::setCodeDimension(TransmissionStruct::counterType newCodeDimension)
{
    codeDimension = newCodeDimension;
}

TransmissionStruct::counterType TransmissionStruct::getControlBitsNumber() const
{
    return controlBitsNumber;
}

void TransmissionStruct::setControlBitsNumber(TransmissionStruct::counterType newControlBitsNumber)
{
    controlBitsNumber = newControlBitsNumber;
}

TransmissionStruct::counterType TransmissionStruct::getWordsGivenToSend() const
{
    return wordsGivenToSend;
}

void TransmissionStruct::setWordsGivenToSend(counterType newOrdsGivenToSend)
{
    wordsGivenToSend = newOrdsGivenToSend;
}

TransmissionStruct::counterType TransmissionStruct::getTotalSendedCodewords() const
{
    return totalSendedCodewords;
}

void TransmissionStruct::setTotalSendedCodewords(counterType newTotalSendedCodewords)
{
    totalSendedCodewords = newTotalSendedCodewords;
}

TransmissionStruct::counterType TransmissionStruct::getNakCounter() const
{
    return nakCounter;
}

void TransmissionStruct::setNakCounter(counterType newNakCounter)
{
    nakCounter = newNakCounter;
}

TransmissionStruct::counterType TransmissionStruct::getAckCounter() const
{
    return ackCounter;
}

void TransmissionStruct::setAckCounter(counterType newAckCounter)
{
    ackCounter = newAckCounter;
}

TransmissionStruct::counterType TransmissionStruct::getRetransmissionCounter() const
{
    return retransmissionCounter;
}

void TransmissionStruct::setRetransmissionCounter(counterType newRetransmissionCounter)
{
    retransmissionCounter = newRetransmissionCounter;
}

TransmissionStruct::counterType TransmissionStruct::getFailedTransmissionCounter() const
{
    return failedTransmissionCounter;
}

void TransmissionStruct::setFailedTransmissionCounter(counterType newFailedTransmissionCounter)
{
    failedTransmissionCounter = newFailedTransmissionCounter;
}

TransmissionStruct::counterType TransmissionStruct::getWrongDetectedFalseCodewords() const
{
    return wrongDetectedFalseCodewords;
}

void TransmissionStruct::setWrongDetectedFalseCodewords(counterType newWrongDetectedFalseCodewords)
{
    wrongDetectedFalseCodewords = newWrongDetectedFalseCodewords;
}

TransmissionStruct::counterType TransmissionStruct::getWrongDetectedPositiveCodewords() const
{
    return wrongDetectedPositiveCodewords;
}

void TransmissionStruct::setWrongDetectedPositiveCodewords(counterType newWrongDetectedPositiveCodewords)
{
    wrongDetectedPositiveCodewords = newWrongDetectedPositiveCodewords;
}

TransmissionStruct::counterType TransmissionStruct::getCorrectSendedCodewords() const
{
    return correctSendedCodewords;
}

void TransmissionStruct::setCorrectSendedCodewords(counterType newCorrectSendedCodewords)
{
    correctSendedCodewords = newCorrectSendedCodewords;
}

TransmissionStruct::counterType TransmissionStruct::getTotalSendedBits() const
{
    return totalSendedCodewords * (codeDimension+controlBitsNumber);
}

TransmissionStruct::counterType TransmissionStruct::getWrongDetectedWordsNumber() const
{
    return wrongDetectedFalseCodewords + wrongDetectedPositiveCodewords;
}
//-------------------------------------------------------------------------------------------------

TransmissionStruct::counterType TransmissionStruct::getRetransmittedBitsNumber() const
{
    return (retransmissionCounter * (codeDimension + controlBitsNumber));
}
//-------------------------------------------------------------------------------------------------
/*
TransmissionStruct::counterType TransmissionStruct::getTransmittedBitsNumber() const
{
    return (wordCounter * (codeDimension + controlBitsNumber));
}
//-------------------------------------------------------------------------------------------------
TransmissionStruct::counterType TransmissionStruct::getFalseBitsNumber() const
{
    return (wrongWordCounter * (codeDimension + controlBitsNumber));
}
//-------------------------------------------------------------------------------------------------
*/
