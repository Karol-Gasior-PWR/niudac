#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <memory>

class FileHandler
{
public:
    FileHandler();
    bool loadFile(const std::string filePath);
    std::shared_ptr<std::vector<bool>>  getData();
private:
    std::shared_ptr<std::vector<bool>> sharedVector = nullptr;
};

#endif // FILEHANDLER_H
