#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <string>
class Message {
public:
	Message(std::string msg, int index);
	int getIndex() const;
	int getNumOfWords() const;
	bool isSendable() const;
	void setIndex(int index);
	std::vector<std::string> saparateTextIntoWords(std::string str);
private:
	static int messageCounter;
	static std::vector<int> totalBanWordsCounters;
	std::vector<std::string> messageWords;
	std::string text;
	int wordsAmount;
	int messageIndex;
};

