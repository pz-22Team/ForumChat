#include "MessageModerator.h"


DWORD __stdcall countBanWords(LPVOID lpParametr) {
	BanWord* banWord = (BanWord*)lpParametr;
	for (auto i : banWord->messageWords) {
		if (i.compare(banWord->word) == 0) {
			InterlockedIncrement(&BanWord::totalNumberOfBunWords);
		}
	}
	return 0;
}

MessageModerator::MessageModerator(std::string msg, std::vector<std::string> banWords, int maxBanAmount) {
	message = msg + " ";
	this->banWords = banWords;
	maxNumOfBanWords = maxBanAmount;
	messageWords = saparateTextIntoWords(message);
	threadsID = new DWORD[banWords.size()];
	threadsHandles = new HANDLE[banWords.size()];
}
MessageModerator::MessageModerator(const MessageModerator& moderator2) {
	message = moderator2.message;
	banWords = moderator2.banWords;
	maxNumOfBanWords = moderator2.maxNumOfBanWords;
	totalNumberOfBanWordsCounter = moderator2.totalNumberOfBanWordsCounter;
	messageWords = moderator2.messageWords;
	threadsID = moderator2.threadsID;
	threadsHandles = moderator2.threadsHandles;
}
MessageModerator::~MessageModerator() {
	delete[] this->threadsHandles;
	delete[] this->threadsID;
}

void MessageModerator::setMessageWords(std::vector<std::string> vect) {
	messageWords = vect;
}

std::vector<std::string> MessageModerator::getMSGWords() {
	return messageWords;
}

void MessageModerator::setBanWords(std::vector<std::string> vect) {
	banWords = vect;
}

std::vector<std::string> MessageModerator::getBanWords() {
	return banWords;
}

void MessageModerator::setMaxNumOfBanWords(int max) {
	maxNumOfBanWords = max;
}

int MessageModerator::getMaxNumOfBanWords() {
	return maxNumOfBanWords;
}

LONG MessageModerator::getTotalNumberOfBanWordsCounter() {
	return totalNumberOfBanWordsCounter;
}

bool MessageModerator::isSendable(std::string message) {
	for (int i = 0; i < (int)banWords.size(); i++) {
		BanWord* banWord = new BanWord(banWords[i], messageWords);
		threadsHandles[i] = CreateThread(0, 0, countBanWords, banWord, NULL, &threadsID[i]);
	}
	WaitForMultipleObjects(banWords.size(), threadsHandles, true, INFINITE);
	totalNumberOfBanWordsCounter = BanWord::totalNumberOfBunWords;
	BanWord::resetTotalNumberOfBunWords();
	return MessageModerator::getTotalNumberOfBanWordsCounter() <= maxNumOfBanWords;
}


std::vector<std::string> MessageModerator::saparateTextIntoWords(std::string str) {
	std::vector<std::string> vect;
	std::string word = "";
	for (auto x : str) {
		if (x == ' ' || x == '\n' || ispunct((int)x)) {
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
