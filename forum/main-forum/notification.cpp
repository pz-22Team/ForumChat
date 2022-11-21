#include "notification.h"

void Notification::SplitIntoWordsAndSet(std::string messageToSplit) {

    int posFirst = messageToSplit.find_first_of("@");
    int posLast = messageToSplit.find_last_of("@");

    std::string sub = messageToSplit.substr(0, posFirst);
    this->amountOfUsers = (stoi(sub));

    sub = messageToSplit.substr(posFirst+1, posLast-posFirst-1);
    this->userName = sub;

    sub = messageToSplit.substr(posLast+1, messageToSplit.size()-1);
    this->message = sub.substr(0, sub.size()-2);
}

Notification::Notification(std::string Info) {
    SplitIntoWordsAndSet(Info);
}

int Notification::getAmountOfUsers() {
    return amountOfUsers;
}

std::string Notification::getUserName() {
    return userName;
}

std::string Notification::getMessage() {
    return message;
}
