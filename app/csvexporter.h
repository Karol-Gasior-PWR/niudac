#ifndef CSVEXPORTER_H
#define CSVEXPORTER_H

#include "simulationdata.h"
#include <QString>
#include <QWidget>

class CSVExporter
{
public:
    CSVExporter(QString &fileName, QWidget * parent, SimulationData &simData);
private:
    void writeToFile();
};

#endif // CSVEXPORTER_H
