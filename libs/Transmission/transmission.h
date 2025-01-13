#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <vector>

#include "channel.h"
#include "coder.h"


#include <qobject.h>
#include"transmissionstruct.h"

class Transmission
{

public:

public:
    Transmission(Coder * coder, Channel * channel, TransmissionStruct::counterType codeDimension, int maxRetransmissions = 3);
    ~Transmission();
    void send(std::shared_ptr<std::vector<bool> > data);
public:
//---------------------------------------------------------------------------------------------------------------------
    TransmissionStruct getData();
private:
    void send(const std::vector<bool> information);
private:
    const TransmissionStruct::counterType codeDimension;
    //TransmissionStruct::counterType transmissionTimeMs = 0;
    TransmissionStruct::counterType wordsGivenToSend = 0;
    TransmissionStruct::counterType totalSendedCodewords= 0;    //all sended codewords, count retransmitted codewords
    TransmissionStruct::counterType nakCounter = 0;
    TransmissionStruct::counterType ackCounter = 0;
    TransmissionStruct::counterType retransmissionCounter = 0;
    TransmissionStruct::counterType failedTransmissionCounter = 0;
    TransmissionStruct::counterType wrongDetectedFalseCodewords= 0; //corrupted information inside codeword detected as UNcorrupted
    TransmissionStruct::counterType wrongDetectedPositiveCodewords= 0; //uncorrupted information inside codeword detected as corrupted
    TransmissionStruct::counterType correctSendedCodewords = 0;     //uncorrupted informaton inside codeword detected as uncorrupted

    std::unique_ptr<Coder> coder;
    std::unique_ptr<Channel> channel;
    int maxRetransmissions;
    int codeWordRetransmissionCounter = 0;
};
//************************************************************************************************


#endif // TRANSMISSION_H
