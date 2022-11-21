#include "BanWord.h"

LONG BanWord::totalNumberOfBunWords;

BanWord::BanWord(std::string word, std::vector<std::string> messages) {
	this->word = word;
	this->messageWords = messages;
}

LONG BanWord::getTotalNumOfBanWordsInMessage() {
	return totalNumberOfBunWords;
}

void BanWord::resetTotalNumberOfBunWords() {
	totalNumberOfBunWords = 0;
}