#include <string>
#include <random>
#include "../inc/CommunicationProtocol.hh"
#include <iomanip>
#include <string>

void waitForAction(){
  char x;
  std::cout << std::endl << "Naciśnij dowolny przycisk aby kontynuować: ";
  std::cin >> x; 
  std::cout << std::endl;
}

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


int main(int argc, char** argv) {
  //random generator
  std::random_device r;
	std::default_random_engine generator(r());
  int rand = 0;

  //communication protocol and variables
  CommunicationProtocol comHandler;
  std::string transmitMess = {};
  std::string receiveMess = {};
  std::string mess = {};
  
  if(argc < 2){
    std::cerr << "Za mało argumentow przy uruchomienu" << std::endl;
    return 0;
  }

  for(int i = 1; i < argc; ++i){
    mess = std::string(argv[i]);
    std::cout << "Wiadomosc nr " << i - 1 << ": " << std::endl << mess << std::endl;

    //waitForAction();
  
    try{
      comHandler.addMessageToBuffor(mess);
    }catch(std::exception & e){
      std::cerr << e.what() << std::endl;
      return 0;
    }

    std::cout << "\nWiadomosc dodana do buffora tx" << std::endl;
    std::cout << "Rozmiar buffora tx: " << comHandler.bufforSize() << std::endl;
    
    //waitForAction();

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

    //waitForAction();
  
    std::cout << "\nRozmiar buffora rx po wysłaniu wiadomości: " << comHandler.bufforSize() << std::endl << std::endl;

    std::cout << std::endl << "Odbrana wiadomosc w bufforze rx" << std::endl;
    comHandler.showRxBuffor();

    try{
      receiveMess = comHandler.getMessage();
    }catch(std::exception & e){
      std::cerr << e.what() << std::endl;
      return 0;
    }

    //waitForAction();

    std::cout << "Odebrana wiadomosc: " << std::endl;
    std::cout << receiveMess << std::endl;

    //waitForAction();
  
  }
	return 0;
}
