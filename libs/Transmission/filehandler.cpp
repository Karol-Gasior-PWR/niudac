#include "filehandler.h"

#include <iostream>
#include <fstream>
#include <QDebug>

FileHandler::FileHandler()
{
}

bool FileHandler::loadFile(const std::string filePath)
{
    sharedVector = std::make_shared<std::vector<bool>>();   //make new vector, old i automatically deleted if not used

    std::ifstream file(filePath, std::ios::binary);
    if(! file.is_open())
    {
        qDebug() << "Cannot open file path: \"" << filePath << "\".";
        return false;
    }

    char byte;
    while(file.read( &byte, 1))
    {
        for(int i=7; i > 0; --i)        //rozbijanie bajtu na bity, od najwiekszego do najmniejszego
            sharedVector->push_back( (byte >> i) & 1);
    }

    file.close();
    return true;
}

std::shared_ptr< std::vector<bool> > FileHandler::getData()
{
    return sharedVector;
}
