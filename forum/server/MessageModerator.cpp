#include "MessageModerator.h"
DWORD __stdcall countBanWords(LPVOID lpParametr) {
	MessageModerator* newThread = (MessageModerator*)lpParametr;
	for (auto i : MessageModerator::messageWords) {
		if (i == newThread->currentBanWord) {
			InterlockedIncrement((LPLONG)MessageModerator::totalNumberOfBanWordsCounter);
		}
	}
	return 0;
}
MessageModerator::MessageModerator() {
	this->threadsHandles = new HANDLE[banWords.size()];
	this->threadsID = new DWORD[banWords.size()];
	for (int i = 0; i <(int) banWords.size(); i++) {
		currentBanWord = banWords[i];
		threadsHandles[i] = CreateThread(0, 0, countBanWords, new MessageModerator(*this), NULL, &threadsID[i]);
	}
}

MessageModerator::MessageModerator(const MessageModerator& moderator2) {
	currentBanWord = moderator2.currentBanWord;
}

MessageModerator::~MessageModerator() {
	message = "";
	totalNumberOfBanWordsCounter = 0;
	messageWords.clear();
	currentBanWord = "";
	delete[] this->threadsHandles;
	delete[] this->threadsID;
}

std::vector<std::string> MessageModerator::saparateTextIntoWords(std::string str) {
	std::vector<std::string> vect;
	std::string word = "";
	for (auto x : str) {
		if (x == ' ' || x == '\n'|| ispunct((int)x)) {
			if (word != "") {
				vect.push_back(word);
				word = "";
			}
		}
		else {
			word = word + x;
		}
	}
	return vect;
}

bool MessageModerator::isSendable(std::string message) {
	bool flag = false;
	if (totalNumberOfBanWordsCounter <= MAX_NUM_OF_BAN_WORDS)
		flag = true;
	return flag;
}

int MessageModerator::getTotalNumberOfBanWordsCounter()
{
	return totalNumberOfBanWordsCounter;
}

void MessageModerator::setMessageWords(std::vector<std::string> vect) {
	messageWords = vect;
}

void MessageModerator::setTotalNumberOfBanWordsCounter(int cnt) {
	if(cnt<0)
		throw MyException("Invalid input number to ban word counter! Counter can not be negative.");
	totalNumberOfBanWordsCounter = cnt;
}

void MessageModerator::setBanWords(std::vector<std::string> vect) { 
	banWords = vect;
}

void MessageModerator::receiveNewMessage(std::string& msg) {
	message = msg;
	messageWords = saparateTextIntoWords(message);
	totalNumberOfBanWordsCounter = 0;

}

std::vector<std::string> MessageModerator::getMSGWords() {
	return messageWords;
}

std::vector<std::string> MessageModerator::getBanWords()
{
	return banWords;
}

void MessageModerator::setCurrentBanWord(std::string banWord) {
	currentBanWord = banWord;
}

std::string MessageModerator::getCurrentBanWord() const {
	return currentBanWord;
}


