#pragma once
#include <string>
#include <vector>

class Notification {
private:
    int amountOfUsers;
    std::string userName;
    std::string message;
    void SplitIntoWordsAndSet(std::string messageToSplit);
public:
    Notification(std::string Info);
    int getAmountOfUsers();
    std::string getUserName();;
    std::string getMessage();;
};


