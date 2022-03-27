#include "prototcolReceiver.hh"

ProtocolReceiver::ProtocolReceiver() {
	packageQuantity = 0;
	idNumber = 0;
}

bool ProtocolReceiver::AddPackage(const std::string & dataFrame) {
	ProtocolPackage package;
	std::string data = dataFrame;

	try {
		package = this->parseDataFrame(dataFrame);

		buffor.insert(package.data, package.position);
	}
	catch (std::exception& e) {
		return false;
	}
	return true;
}

void ProtocolReceiver::showBuffor() {
	buffor.print();
}

ProtocolPackage ProtocolReceiver::parseDataFrame(const std::string & dataFrame) {
	std::string data = dataFrame;
	uint8_t frameID = dataFrame[0];
	uint8_t frameNumber = dataFrame[1];
	uint8_t checkSum = dataFrame[FRAME_SIZE - 1];

	if (idNumber == 0 ) { //check special number
		idNumber = frameID;
	}
	else if(idNumber != frameID) {
		throw std::exception("Invalid id number, message buffor cleared");
	}

	if (frameNumber == 0) { //check frame number
		packageQuantity = data[2];
		data = data.substr(3, FRAME_SIZE-4);
	}
	else {
		data = data.substr(2, FRAME_SIZE-3);
	}
	

	return ProtocolPackage(data, frameNumber);
}

bool ProtocolReceiver::allFrameReceived() {
	if (packageQuantity == 0 || packageQuantity != buffor.size()) {
		return false;
	}

	return true;
}

std::string ProtocolReceiver::getMessage() {
	std::string result = {};

	if (!this->allFrameReceived()) {
		throw std::exception("Not all frame received!");
	}

	while (!buffor.isEmpty()) {
		result += buffor.removeMin();
	}

	return result;
}

bool ProtocolReceiver::checkSumCorrect(const std::string& data) {
	return true;
}