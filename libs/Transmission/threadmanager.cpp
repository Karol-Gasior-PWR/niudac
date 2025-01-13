#include "threadmanager.h"




#include "filehandler.h"
#include "bscchannel.h"
#include "paritycoder.h"
#include "transmission.h"
//#include <iostream>
#include <memory>
#include <qelapsedtimer.h>
#include <qobjectdefs.h>
#include <thread>
#include <vector>
#include <mutex>

#include <QDebug>



//--------------------------------------------------------------------------------------------------------
//one simulation for specific information sequene length
TransmissionStruct simulation(Coder * cod, Channel * chan, unsigned int k, std::shared_ptr< std::vector<bool> > data)
{
    Transmission tr{cod,chan, k};
    tr.send(data);
    return tr.getData();
}
//--------------------------------------------------------------------------------------------------------
std::vector<TransmissionStruct> func(Coder * cod, Channel * chan, std::string file_path, std::pair<uint, uint> informationSequenceRange)
{
    std::vector<std::thread> threads;  // Wektory wątków
    std::vector<TransmissionStruct> results{informationSequenceRange.second - informationSequenceRange.first};  // Wektory przechowujące TransmissionStruct wynikowe
    std::mutex mtx;  // Mutex do synchronizacji zapisów w tablicy

    //-------------------------------------------------------------------------
    FileHandler fileHandler;
    fileHandler.loadFile(file_path);
    std::shared_ptr< std::vector<bool> > data = fileHandler.getData();
    //-------------------------------------------------------------------------

    QElapsedTimer clock;
    clock.start();


    // Tworzenie i uruchamianie wątków
    for (int i = informationSequenceRange.first; i < informationSequenceRange.second; ++i) {
        threads.push_back(std::thread([i, &results, &mtx, chan, &cod, &data, &informationSequenceRange]()
            {
            TransmissionStruct result = simulation(cod->clone(), chan->clone(), i, data);
            // Synchronizacja zapisu do wektora
            std::lock_guard<std::mutex> lock(mtx);
            results[i-informationSequenceRange.first] = result;  // Dodajemy TransmissionStruct do wektora
        }));
    }

    // Czekamy, aż wszystkie wątki zakończą działanie
    for (auto& t : threads) {
        t.join();
    }
    qDebug() << "Calculation time: " << clock.elapsed()/1000 << " [s]";
    return results;
}
