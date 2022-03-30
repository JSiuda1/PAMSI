#pragma once 

#include "PriorityQueue.hh"
#include "linkedList.hh"
#include <string>
#include <iostream>
#include <exception>

#define FRAME_LENGTH 8
#define FIRST_FRAME_DATA_LENGTH (FRAME_LENGTH - 4)
#define OTHER_FRAME_DATA_LENGTH (FRAME_LENGTH - 3)

class CommunicationProtocol{
  //receive
	PriorityQueue<std::string> rxBuffor;
	uint8_t packageQuantity;
	uint8_t idNumberRx;

  //transmit
  LinkedList<std::string> txBuffor;
	uint8_t idNumberTx;

public:
	CommunicationProtocol();
  //receive
	void AddPackage(const std::string& dataFrame);
	bool allFrameReceived();
	std::string getMessage();
	void showRxBuffor() const;
  //transmit
	void addMessageToBuffor(const std::string & _mess);
	std::string sendBufferElement(const int& elem);
	int bufforSize() const;
	bool bufforIsEmpty() const;

private:
  //receive
	bool checkSumCorrect(const std::string& data, const uint8_t& checksum);
	void parseDataFrame(const std::string& dataFrame, std::string & dataOutput, uint8_t & priority);
	//transmit
  uint8_t checkSumCount(const std::string & mess);
	void idTxHandler();
	void clear();
};