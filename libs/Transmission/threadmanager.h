#ifndef THREADMANAGER_H
#define THREADMANAGER_H




#include "channel.h"
#include "coder.h"
#include "transmissionstruct.h"

//--------------------------------------------------------------------------------------------------------
// Klasa przechowująca dane

std::vector<TransmissionStruct> func(Coder * codOrg, Channel * chanOrg, std::string file_path, std::pair<uint, uint> informationSequenceRange);

#endif // THREADMANAGER_H
