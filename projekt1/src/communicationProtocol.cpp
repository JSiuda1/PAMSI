#include "../inc/CommunicationProtocol.hh"
#include <stdexcept>

void CommunicationProtocol::addReceivedFrame(const std::string& dataFrame) {
	try{
    rx.AddPackage(dataFrame);
  }catch(std::exception e){
    throw;
  }
}

void CommunicationProtocol::receiveBufforPrint(){
  rx.showbuffor();
}

bool CommunicationProtocol::allFrameReceived(){
  return rx.allFrameReceived();
}

std::string CommunicationProtocol::getMessage(){
  std::string result = {};
  
  try{
    result = rx.getMessage();
  }catch(std::exception e){
    throw;
  }
  
  return result;
}

//transmit
void CommunicationProtocol::createDataPackage(const std::string & mess){
  try{
    tx.addMessageToBuffor(mess);
  }catch(std::exception e){
    throw;
  }
}

int CommunicationProtocol::transmitBufforSize(){
  return tx.bufforSize();
}


bool CommunicationProtocol::transmitBufforIsEmpty(){
  return tx.bufforIsEmpty();
}

std::string CommunicationProtocol::sendBufforFrame(const int & position){
  std::string result = {};
  try{
    result = tx.sendBufforElement(position);
  }catch(std::exception){
    throw;
  }

  return result;
}