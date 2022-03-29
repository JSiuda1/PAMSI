#include "../inc/CommunicationProtocol.hh"
#include <stdexcept>
CommunicationProtocol::CommunicationProtocol(){
  packageQuantity = 0;
  idNumberRx = 0;
  idNumberTx = 0; //TODO
}

//receive
void CommunicationProtocol::AddPackage(const std::string& dataFrame) {
  std::string parsedData = {};
  uint8_t priority = {};
	
	if(parseDataFrame(dataFrame, parsedData, priority)){
		try{
			rxBuffor.insert(parsedData, priority);
		}catch(std::exception &e){
			throw;
		}
  }else{
    throw std::invalid_argument("Invalid argument during data parsing");
  }	
	
}

bool CommunicationProtocol::parseDataFrame(const std::string& dataFrame, std::string & dataOutput, uint8_t & priority) {
	std::string data = dataFrame;
	uint8_t dataSize = (uint8_t)dataFrame.length();
	uint8_t frameID = (uint8_t)dataFrame[0];
	uint8_t frameNumber = (uint8_t)dataFrame[1];
	uint8_t checkSum = (uint8_t)dataFrame[dataSize - 1];
	
	if (idNumberRx == 0) { //first package
		idNumberRx = frameID;
	}
	else if (idNumberRx != frameID) { 
    return false;
  }	

	//checksum check
	if (!checkSumCorrect(data, checkSum)) {
		return false;
	}

	if (frameNumber == 0) { //check frame number
		packageQuantity = data[2];
		data = data.substr(3, dataSize - 4);
	}
	else {
		data = data.substr(2, dataSize - 3); 
	}
	
  dataOutput = data;
  priority = frameNumber;
  return true;
}

bool CommunicationProtocol::allFrameReceived() {
	if (packageQuantity == 0 || packageQuantity != rxBuffor.size()) {
		return false;
	}

	return true;
}

std::string CommunicationProtocol::getMessage() {
	std::string result = {};

	if (!allFrameReceived()) {
		throw std::logic_error("Not all frame received!");
	}

	while (!rxBuffor.isEmpty()) {
		try{
			result += rxBuffor.removeMin();
		}catch(std::exception & e){
		  throw;
    } 
	}

	clear();
	return result;
}

bool CommunicationProtocol::checkSumCorrect(const std::string& data, const uint8_t& checksum) {
	uint8_t dataLength = (uint8_t)data.length();
	uint8_t countedChecksum = 0xff;
	uint8_t tmp = 0;
	for (int i = 1; i < (dataLength - 1); ++i) {
		tmp += data[i];
	}
	countedChecksum -= tmp;

	return countedChecksum == checksum ? true : false;
}

void CommunicationProtocol::showRxBuffor() const{
	rxBuffor.print();
}


//transmit
void CommunicationProtocol::addMessageToBuffor(const std::string & _mess) {
	std::string mess = _mess;
	std::string subMess = {};
	uint8_t frameQuantity = 0;
	
	idTxHandler();

	frameQuantity = mess.length() > (FRAME_LENGTH - FIRST_FRAME_DATA_LENGTH) ? (uint8_t)((mess.length() - FIRST_FRAME_DATA_LENGTH) / OTHER_FRAME_DATA_LENGTH) + 2 : 1;

	if(frameQuantity > UINT8_MAX){
		throw std::out_of_range("Message is to big");
	}

	for (int i = 0; i < frameQuantity; ++i) {
		subMess += idNumberTx;
		subMess += i;

		if (i == 0) {
			subMess += frameQuantity;
			subMess += mess.substr(0, FIRST_FRAME_DATA_LENGTH);
			mess.erase(0, FIRST_FRAME_DATA_LENGTH);
		}
		else {
			subMess += mess.substr(0, OTHER_FRAME_DATA_LENGTH);
			mess.erase(0, OTHER_FRAME_DATA_LENGTH);
		}

		subMess += checkSumCount(subMess);//checksum
		
		try{
			txBuffor.push(subMess);
		}catch(std::exception &e){
			throw;
		}

		subMess.clear();
	}
}


std::string CommunicationProtocol::sendBuffer(const int & elem) {
	std::string mess = {};
	
	try{
		mess = txBuffor.getElement(elem);
	}catch(std::exception &e){
		throw;
	}

	return mess;
}

int CommunicationProtocol::bufforSize() const {
	return txBuffor.size();
}

bool CommunicationProtocol::bufforIsEmpty() const {
	return txBuffor.isEmpty();
}

uint8_t CommunicationProtocol::checkSumCount(const std::string &  mess) {
	uint8_t checksum = 0xFF;
	uint8_t messLength = (uint8_t)mess.length();
	uint8_t tmp = 0;

	for (int i = 1; i < messLength; ++i) {
		tmp += mess[i];
	}

	checksum -= tmp;
	return checksum;
}

void CommunicationProtocol::idTxHandler(){
	(idNumberTx + 1) == 0 ? idNumberTx = 1 : idNumberTx += 1;
}

void CommunicationProtocol::clear(){
	idNumberRx = 0;
	packageQuantity = 0;
	
	if(!txBuffor.isEmpty()){
		txBuffor.clear();
	}
	
}