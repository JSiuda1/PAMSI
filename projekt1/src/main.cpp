//#include "../inc/PriorityQueue.hh"
#include "../inc/prototcolReceiver.hh"
#include "../inc/protocolTransmiter.hh"
#include <string>
#include <random>


int main() {
	std::random_device r;
	std::default_random_engine generator(r());

	Transmiter transmiter;
	Receiver receiver;
	std::string mess = "I've seen things you people wouldn't believe... Attack ships on fire off the shoulder of Orion... I watched C-beams glitter in the dark near the Tannhäuser Gate. All those moments will be lost in time, like tears in rain... Time to die.";
	
	std::cout << mess << std::endl;
	if (!transmiter.addMessage(mess)) {
		std::cout << "Something goes wrong" << std::endl;
	}

	
	std::cout << transmiter.bufforSize() << std::endl;
	
	std::cout << "Wysy³anie paczek" << std::endl;
	try {
		while (!transmiter.bufforIsEmpty()) {
			std::uniform_int_distribution<int> distribution(0, transmiter.bufforSize() - 1);
			int rand = distribution(generator);
			//std::cout << "RAND: " << rand << std::endl;
			
			mess = transmiter.sendBuffer(rand);
			//std::cout << elem << std::endl << std::endl;
			//mess = transmiter.sendBuffer();
			std::cout << mess << std::endl;
			receiver.AddPackage(mess);
		}
	}
	catch (std::exception& e){
		std::cerr << e.what() << std::endl;
	}
	std::cout << receiver.allFrameReceived() << std::endl;
	receiver.showBuffor();
	std::cout << receiver.getMessage() << std::endl;

	return 0;
}