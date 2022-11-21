#pragma once
#include <fstream>
#include <ctime>
#include "myexception.h"

#include <fstream>

class Logger {
private:
    std::ofstream file;
public:
    Logger();
    void log(std::string type, std::string message);
};
