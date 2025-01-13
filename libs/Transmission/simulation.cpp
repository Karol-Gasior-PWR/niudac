#include "simulation.h"

#include <thread>
#include <mutex>


Simulation::Simulation() {}
//---------------------------------------------------------------------------------------------------------------------
void Simulation::setSimulationData(std::string path)
{
    fileHandler.loadFile(path);
}
//---------------------------------------------------------------------------------------------------------------------
void Simulation::simulate(unsigned int startCodeDimension, unsigned int stopCodeDimension)
{
    std::vector<std::thread> threads;  // Wektory wątków
    std::vector<TransmissionStruct> results{stopCodeDimension-startCodeDimension};  // Wektory przechowujące TransmissionStruct wynikowe
    std::mutex mtx;  // Mutex do synchronizacji zapisów w tablicy

    //-------------------------------------------------------------------------
    std::shared_ptr< std::vector<bool> > data = fileHandler.getData();
    //-------------------------------------------------------------------------

    QElapsedTimer clock;    //to measure calculation time
    clock.start();

    // Tworzenie i uruchamianie wątków
    for (int i = startCodeDimension; i < stopCodeDimension; ++i) {
        threads.push_back(std::thread([i, &results, &mtx, &data, &startCodeDimension, this]()
          {
              TransmissionStruct result = simulationStep(i);
              // Synchronizacja zapisu do wektora
              std::lock_guard<std::mutex> lock(mtx);
              results[i-startCodeDimension] = result;  // Dodajemy TransmissionStruct do wektora
          }));
    }

    // Czekamy, aż wszystkie wątki zakończą działanie
    for (auto& t : threads) {
        t.join();
    }
    calculationTime = clock.elapsed()/1000; // miliseconds to seconds
}
//---------------------------------------------------------------------------------------------------------------------
TransmissionStruct Simulation::simulationStep(unsigned int codeDimension)
{

}
