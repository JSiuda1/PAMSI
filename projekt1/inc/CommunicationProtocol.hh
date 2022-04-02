#pragma once 

#include "Receiver.hh"
#include "Transmiter.hh"

class CommunicationProtocol{
  Receiver rx;
  Transmiter tx;

public:
  CommunicationProtocol() = default;
  //receive
  void addReceivedFrame(const std::string & mess);
  void receiveBufforPrint();
  bool allFrameReceived();
  std::string getMessage();
  //transmit
  void createDataPackage(const std::string & mess);
  int transmitBufforSize();
  bool transmitBufforIsEmpty();
  std::string sendBufforFrame(const int & position);

};