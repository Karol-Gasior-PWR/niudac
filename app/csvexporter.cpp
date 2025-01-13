#include "csvexporter.h"

#include <QFileInfo>
#include <QMessageBox>

CSVExporter::CSVExporter(QString & fileName, QWidget * parent, SimulationData & simData)
{
    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        QString path = fileInfo.absolutePath();
        QString baseName = fileInfo.baseName();
        QString extension = fileInfo.suffix().isEmpty() ? ".txt" : "." + fileInfo.suffix();

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            // Tworzymy obiekt QTextStream do zapisu tekstu do pliku
            QTextStream out(&file);

            //columns names
            out << "CodeDimension" << ","
                << "ControlBitsNumber" << ","
                << "WordsGivenToSend" << ","
                << "TotalSendedCodewords" << ","
                << "NakCounter" << ","
                << "AckCounter" << ","
                << "RetransmissionCounter" << ","
                << "FailedTransmissionCounter" << ","
                << "WrongDetectedFalseCodewords" << ","
                << "WrongDetectedPositiveCodewords" << ","
                << "CorrectSendedCodewords" << ","
                << "\n";  // end of line

            // Iterujemy po wierszach danych
            for (const auto& row : simData.getSimData())
            {
                out << row.getCodeDimension() << ","
                    << row.getControlBitsNumber() << ","
                    << row.getWordsGivenToSend() << ","
                    << row.getTotalSendedCodewords() << ","
                    << row.getNakCounter() << ","
                    << row.getAckCounter() << ","
                    << row.getRetransmissionCounter() << ","
                    << row.getFailedTransmissionCounter() << ","
                    << row.getWrongDetectedFalseCodewords() << ","
                    << row.getWrongDetectedPositiveCodewords() << ","
                    << row.getCorrectSendedCodewords() << ","
                    << "\n";  // end of line
            }
            file.close();  // Zamykanie pliku po zapisaniu danych
            QMessageBox::information(parent, "Sukces", "Plik został zapisany jako: " + fileName);
        } else {
            QMessageBox::warning(parent, "Błąd", "Nie udało się otworzyć pliku do zapisu.");
        }
    } else {
        // Użytkownik anulował wybór pliku
        QMessageBox::warning(parent, "Anulowano", "Nie wybrano żadnego pliku.");
    }
}

void CSVExporter::writeToFile()
{

}
