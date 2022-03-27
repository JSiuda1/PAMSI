#include "../inc/FifoList.hh"
#include "../inc/prototcolReceiver.hh"

#include <string>

int main(){
	ProtocolReceiver receiver;
	std::string mess = "D05ABCD8";
	if (receiver.AddPackage(mess)) {
		std::cout << "Udalo sie" << std::endl;
	}
	mess = "D";
	uint8_t id = 0;
	mess += static_cast<uint8_t>(id);
	id = 2;
	mess += static_cast<uint8_t>(id);
	mess += "CZESC";
	receiver.AddPackage(mess);
	std::cout << receiver.allFrameReceived() << std::endl;
	receiver.showBuffor();
	std::cout << receiver.getMessage() << std::endl;
	//queue.print();

  return 0;
}