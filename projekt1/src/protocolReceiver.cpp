#include "prototcolReceiver.hh"

Receiver::Receiver() {
	packageQuantity = 0;
	idNumber = 0;
}

bool Receiver::AddPackage(const std::string& dataFrame) {
	ProtocolPackage package;
	std::string data = dataFrame;

	try {
		package = parseDataFrame(dataFrame);

		buffor.insert(package.data, package.position);
	}
	catch (std::exception& e) {
		return false;
	}
	return true;
}

void Receiver::showBuffor() {
	buffor.print();
}

ProtocolPackage Receiver::parseDataFrame(const std::string& dataFrame) {
	std::string data = dataFrame;
	uint8_t dataSize = dataFrame.length();
	uint8_t frameID = dataFrame[0];
	uint8_t frameNumber = dataFrame[1];
	uint8_t checkSum = dataFrame[dataSize - 1];

	if (idNumber == 0) { //check special number
		idNumber = frameID;
	}
	else if (idNumber != frameID) {
		throw std::exception("Invalid id number, message buffor cleared");
	}

	//checksum check
	if (!checkSumCorrect(data, checkSum)) {
		throw std::exception("Check sum incorrect");
	}

	if (frameNumber == 0) { //check frame number
		packageQuantity = data[2];
		data = data.substr(3, dataSize - 4);
	}
	else {
		data = data.substr(2, dataSize - 3); 
	}


	return ProtocolPackage(data, frameNumber);
}

bool Receiver::allFrameReceived() {
	if (packageQuantity == 0 || packageQuantity != buffor.size()) {
		return false;
	}

	return true;
}

std::string Receiver::getMessage() {
	std::string result = {};
	std::string resultPart = {};

	if (!this->allFrameReceived()) {
		throw std::exception("Not all frame received!");
	}

	while (!buffor.isEmpty()) {
		if (buffor.removeMin(resultPart)) {
			result += resultPart;
		}
		else {
			throw std::exception("Unable to removeMin");
		}
	}

	return result;
}

bool Receiver::checkSumCorrect(const std::string& data, const uint8_t& checksum) {
	uint8_t dataLength = data.length();
	uint8_t countedChecksum = 0xff;
	uint8_t tmp = 0;
	for (int i = 1; i < (dataLength - 1); ++i) {
		tmp += data[i];
	}
	countedChecksum -= tmp;

	return countedChecksum == checksum ? true : false;
}