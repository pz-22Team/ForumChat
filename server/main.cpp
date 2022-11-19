#include "MessageModerator.h"
#include <conio.h>

int main(int argc, char** argv) {
	std::vector < std::string> vectBanWords = { "Putin", "orc", "gavryk" };
	std::string str = "gavryk Invalid Putin Putin number to ban word Putin! Counter orc not orc be negative.";

	std::cout << "All banned words, which must be limited for using:";
	int maxBanWords = 5;

	MessageModerator* moderator = new MessageModerator(str, vectBanWords, maxBanWords);

	for (auto i : moderator->getBanWords()) {
		std::cout << i << " ";
	}
	std::cout << "\n\nThere is received message from server: \"" << str << "\"" << std::endl << std::endl;

	std::cout << "There are " << moderator->getMSGWords().size() << " words in  message" << std::endl;

	if (moderator->isSendable(str)) {
		std::cout << "Message is acceptable! Amount of banned words is " 
			<< moderator->getTotalNumberOfBanWordsCounter()<< "!" << std::endl;
	} else {
		std::cout << "Message is unacceptable! Amount of banned words is "
			<< moderator->getTotalNumberOfBanWordsCounter() << "!" << std::endl;
	}
	delete moderator;


	_getch();
	return 0;
}