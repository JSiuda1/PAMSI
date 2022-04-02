#include "../inc/Receiver.hh"
#include <stdexcept>

Receiver::Receiver(): packageQuantity(0), idNumber(0) {}

//receive
void Receiver::AddPackage(const std::string& dataFrame) {
  std::string parsedData = {};
  uint8_t priority = {};
	
		try{
			parseDataFrame(dataFrame, parsedData, priority);
			buffor.insert(parsedData, priority);
		}catch(std::exception e){
			throw;
		}
}

void Receiver::parseDataFrame(const std::string& dataFrame, std::string & dataOutput, uint8_t & priority) {
	std::string data = dataFrame;
	uint8_t dataSize = (uint8_t)dataFrame.length();
	uint8_t frameID = (uint8_t)dataFrame[0];
	uint8_t frameNumber = (uint8_t)dataFrame[1];
	uint8_t checkSum = (uint8_t)dataFrame[dataSize - 1];
	
	if (idNumber == 0) { //first package
		idNumber = frameID;
	}
	else if (idNumber != frameID) { 
    return; //wrong package receive
  }	

	//checksum check
	if (!checkSumCorrect(data, checkSum)) {
		//checksum error handling, timeout is necessary here
		throw std::logic_error("Package demaged, protocol crashed");
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
}

bool Receiver::allFrameReceived() {
	if (packageQuantity == 0 || packageQuantity != buffor.size()) {
		return false;
	}

	return true;
}

std::string Receiver::getMessage() {
	std::string result = {};

	if (!allFrameReceived()) {
		throw std::logic_error("Not all frame received!");
	}

	while (!buffor.isEmpty()) {
		try{
			result += buffor.removeMax();
		}catch(std::exception e){
		  throw;
    } 
	}

	clear();
	return result;
}

bool Receiver::checkSumCorrect(const std::string& data, const uint8_t& checksum) {
	uint8_t dataLength = (uint8_t)data.length();
	uint8_t countedChecksum = 0xff;
	uint8_t tmp = 0;
	for (int i = 1; i < (dataLength - 1); ++i) {
		tmp += data[i];
	}
	countedChecksum -= tmp;

	return countedChecksum == checksum ? true : false;
}

void Receiver::showbuffor() const{
	buffor.print();
}

void Receiver::clear(){
	idNumber = 0;
	packageQuantity = 0;
	
	if(!buffor.isEmpty()){
		buffor.clear();
	}
}