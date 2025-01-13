#include "transmission.h"
#include <qdebug.h>


using namespace std;


Transmission::Transmission(Coder *coder, Channel *channel, TransmissionStruct::counterType codeDimension, int maxRetransmissions)
:
    coder{coder->clone()},
    channel{channel->clone()},
    codeDimension{codeDimension},
    maxRetransmissions{maxRetransmissions}
{

}
//-------------------------------------------------------------------------------------------------
Transmission::~Transmission()
{

}

void Transmission::send(const std::vector<bool> information)
{
    /*information jest kopiowane poniewaz bedzie zmieniane wewnatrz funkcji
    */
    //#0
    ++totalSendedCodewords;
    //#1 encode a signle codeword
    auto codeword { coder->encode(information) };
    //#2 add interference from channel transmision
    channel->applyInterference(codeword);
    //#3 check if encoded word is valid
    bool isValid = coder->isValid(codeword);
    //#4 decode
    codeword = coder->decode(codeword);

    if(isValid) //Ack
    {
        ++ackCounter;

        codeWordRetransmissionCounter = 0;
        //qDebug() << "Ack received";
        if( information != codeword)    // not recognized false information
            ++wrongDetectedFalseCodewords;  //corrupted information inside codeword detected as UNcorrupted
        else    //transmission correct
            ++correctSendedCodewords;
    }
    else    //Nak
    {
        ++nakCounter;
        //qDebug() << "Nak received";
        if( information == codeword)    // correct info recognized as false
            ++wrongDetectedPositiveCodewords= 0;

        nakCounter++;
        //retransmission
        if(codeWordRetransmissionCounter < maxRetransmissions)
        {
            ++retransmissionCounter; //for statistic
            ++codeWordRetransmissionCounter;    //protocol counter
            send(information);
        }else   //transmission failed, to many attempts
        {
            ++failedTransmissionCounter;        //counter for statistic
            codeWordRetransmissionCounter = 0;  //protocol counter
        }

    }

}

void Transmission::send(shared_ptr<std::vector<bool> > data)
{
    //#2 evaluete information number
    unsigned int infoNumber = data->size() / codeDimension;
    auto begin = data->begin();
    for(int i=0; i < infoNumber; ++i)
    {
        vector<bool> information {begin, begin + codeDimension};
        begin += codeDimension;
        ++wordsGivenToSend;
        send(information);
    }

}

TransmissionStruct Transmission::getData()
{

    TransmissionStruct data{
                    codeDimension,
                    coder->getControlBitsNumber(codeDimension),
                    wordsGivenToSend,
                    totalSendedCodewords,
                    nakCounter,
                    ackCounter,
                    retransmissionCounter,
                    failedTransmissionCounter,
                    wrongDetectedFalseCodewords,
                    wrongDetectedPositiveCodewords,
                    correctSendedCodewords
                    };


    return data;
}
//=================================================================================================
//=================================================================================================

//=================================================================================================
