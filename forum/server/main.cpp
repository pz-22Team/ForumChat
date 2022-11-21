#include "MyServerSocket.h"
#include <conio.h>
#include <sstream>

std::string getPortFromFile(std::string fileName);
std::vector<std::string> getBanWordsFromFile(std::string fileName);

int main(int argc, char** argv) {
	std::cout << "new version" << std::endl;
	try {
		std::vector < std::string> vectBanWords = getBanWordsFromFile("ban-words.txt");
		int index = 0;
		std::cout << "All banned words, which must be limited for using: ";
		for (auto i : vectBanWords) {
            if(index++ > 0)
			std::cout << i << " ";
		}
		std::cout << std::endl << std::endl;

		std::string message;;
		std::string port = getPortFromFile("server-config.txt");
		int maxBanWords;// = atoi(argv[1]);
		maxBanWords = stoi(vectBanWords[0]);

		bool respond;

		MyServerSocket* serverSock = new MyServerSocket(port);
		std::cout << "Server is listening port: " << port << std::endl;

		while (true) {
			serverSock->acceptClient();
			message = serverSock->receiveMSG();
			MessageModerator* moderator = new MessageModerator(message, vectBanWords, maxBanWords);
			std::cout << "--------------------------------------------------------------------------------" << std::endl;
			std::cout << "There is received message from server: \"" << message << "\"" << std::endl << std::endl;

			std::cout << "There are " << moderator->getMSGWords().size() << " words in message" << std::endl;
			respond = moderator->isSendable();
			if (respond) {
				std::cout << "Message is acceptable! Amount of banned words is "
					<< moderator->getTotalNumberOfBanWordsCounter() << "!" << std::endl;
			}
			else {
				std::cout << "Message is unacceptable! Amount of banned words is "
					<< moderator->getTotalNumberOfBanWordsCounter() << "!" << std::endl;
			}

			delete moderator;
			serverSock->sendAnswer(respond);
			serverSock->shutDownClient();
			std::cout << "--------------------------------------------------------------------------------"
				<< std::endl << std::endl;
		}
		delete serverSock;
	}
	catch (const MyException& e) {
		std::cout << e.what();
	}
	
	_getch();
	return 0;
}

std::string getPortFromFile(std::string fileName) {
	std::string line;
	std::ifstream in(fileName);

	if (in.is_open()) {
		getline(in, line);
	}
	else {
		std::cout << "failed to open";
	}
	in.close();

	std::string port = line.substr(line.find_first_of("=") + 1, line.size() - 1);

	return std::to_string(atoi(port.c_str()));
}

std::vector<std::string> getBanWordsFromFile(std::string fileName) {
	std::string line;
	std::ifstream in(fileName);

	if (in.is_open())
	{
		getline(in, line);
	}
	std::vector<std::string> BanWords;
	std::istringstream ss(line);
	std::string word;

	while (ss >> word) {
		BanWords.push_back(word);
	}
	return BanWords;
}
