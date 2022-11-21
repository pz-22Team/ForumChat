#include "logger.h"

Logger::Logger() {
    file.open("log.txt", std::ios::app);
    if (!file.is_open()) {
        throw MyException("Cannot open log file!");
    }
}

void Logger::log(std::string type, std::string message) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string time = "";

    std::string hours = std::to_string(ltm->tm_hour);
    time += hours.size() == 1 ? "0" + hours : hours;
    time +=  + ":";

    std::string min = std::to_string(ltm->tm_min);
    time += min.size() == 1 ? "0" + min : min;
    time += ":";

    std::string sec = std::to_string(ltm->tm_sec);
    time += sec.size() == 1 ? "0" + sec : sec;

    std::string toWrite = "[";
    toWrite += time + "]: " + type + " - " + message + "\n";
    file << toWrite;
    file.flush();
}
