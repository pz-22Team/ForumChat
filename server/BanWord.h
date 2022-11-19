#pragma once
#include <string>
#include <vector>
#include <Windows.h>

class BanWord {
public:
	std::string word;
	std::vector<std::string> messageWords;
	static LONG totalNumberOfBunWords;
	static void resetTotalNumberOfBunWords();

	BanWord(std::string word, std::vector<std::string> messages);
	static LONG getTotalNumOfBanWordsInMessage();
};

