#include "../inc/prototcolReceiver.hh"
#include "../inc/protocolTransmiter.hh"
#include <string>
#include <random>
#include "../inc/CommunicationProtocol.hh"
#include <iomanip>

void printStringHex(const std::string & mess) {
  int i = 0;
  for (char var : mess) {
    if (i > 1 && i < (FRAME_LENGTH - 1)) {
      std::cout << var;
    }
    else {
      std::cout << " " << static_cast<int>(var) << "  ";
    }
    i++;
  }
  std::cout << std::endl;
}

int main() {
	std::random_device r;
	std::default_random_engine generator(r());

  CommunicationProtocol comHandler;
  int rand = 0;
  std::string transmitMess;
  std::string receiveMess;
  std::string mess = "I've seen things you people wouldn't believe... Attack ships on fire off the shoulder of Orion... I watched C-beams glitter in the dark near the Tannhauser Gate. All those moments will be lost in time, like tears in rain... Time to die.";
  //std::string mess = "test";
  std::cout << "Wiadomosc: " << std::endl << mess << std::endl;

  try{
    comHandler.addMessageToBuffor(mess);
  }catch(std::exception & e){
    std::cerr << e.what() << std::endl;
    return 0;
  }

  std::cout << "Wiadomosc dodana do buffora tx" << std::endl;
  std::cout << "Rozmiar buffora tx: " << comHandler.bufforSize() << std::endl << std::endl;

  std::cout << "Wysylanie wiadomosci: " << std::endl;

  while(!comHandler.bufforIsEmpty()){
    //simulate random data transmit
    std::uniform_int_distribution<int> distribution(0, comHandler.bufforSize() - 1); 
    rand = distribution(generator);

    try{
      transmitMess = comHandler.sendBuffer(rand); 
      printStringHex(transmitMess);
      comHandler.AddPackage(transmitMess);
    }catch(std::exception &e){
      std::cerr << e.what() << std::endl;
      return 0;
    }
  }

  std::cout << std::endl << "Odbrana wiadomosc w bufforze rx" << std::endl;
  comHandler.showRxBuffor();

  if (comHandler.allFrameReceived()) {
    receiveMess = comHandler.getMessage();
  }

  std::cout << "Odebrana wiadomosc: " << std::endl;
  std::cout << receiveMess << std::endl;

	return 0;
}