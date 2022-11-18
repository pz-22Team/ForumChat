#include "MessageModerator.h"


 int MessageModerator::totalNumberOfBanWordsCounter = 0;
 std::string MessageModerator::message = "";
 std::vector<std::string> MessageModerator::messageWords = std::vector<std::string>(1,"");
 std::vector<std::string> MessageModerator::banWords = { "Putin", "orc", "gavryk" };
int main() {
	std::cout << "All banned words, which must be limited for using :" << std::endl;
	for (auto i : MessageModerator::getBanWords()) {
		std::cout << i << " ";
	}
	std::string str = "Invalid Putin number to ban word Putin! Counter orc not be negative.";
	std::cout << "\nThere is received message from server: \"" << str << "\"" << std::endl;
	MessageModerator::receiveNewMessage(str);
	std::cout << "All words of received message:"<<std::endl;
	for (auto i : MessageModerator::getMSGWords()) {
		std::cout << i << std::endl;
	}
	MessageModerator* moderator = new MessageModerator();
	if (MessageModerator::isSendable(str)) {
		std::cout << "Message is acceptable! Amount of banned wors is " << MessageModerator::getTotalNumberOfBanWordsCounter() << "!" << std::endl;
	}
	delete moderator;
	return 0;
}