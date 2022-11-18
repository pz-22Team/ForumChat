#pragma once
#include "myexception.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <string>
const int MAX_NUM_OF_BAN_WORDS = 5;
class MessageModerator {
	friend DWORD WINAPI countBanWords(LPVOID lpParametr);
public:

	static bool isSendable(std::string message);
	static int getTotalNumberOfBanWordsCounter();
	static void setMessageWords(std::vector < std::string> vect);
	static void setTotalNumberOfBanWordsCounter(int cnt);
	static void setBanWords(std::vector < std::string> vect);
	static void receiveNewMessage(std::string &msg);
	static std::vector<std::string> getMSGWords();
	static std::vector<std::string> getBanWords();
	void setCurrentBanWord(std::string banWord);
	std::string getCurrentBanWord() const;
	MessageModerator();
	MessageModerator(const MessageModerator&  moderator2);
	~MessageModerator();
private:
	static std::vector<std::string> saparateTextIntoWords(std::string str);
    static int totalNumberOfBanWordsCounter;
	static std::string message;
	static std::vector<std::string> messageWords;
	static std::vector<std::string> banWords;
	std::string currentBanWord;
	DWORD* threadsID;
	HANDLE* threadsHandles;

};

