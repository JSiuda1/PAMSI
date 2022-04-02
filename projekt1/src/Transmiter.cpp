#include "../inc/Transmiter.hh"

Transmiter::Transmiter(){
  idHandler();
}

void Transmiter::addMessageToBuffor(const std::string & _mess) {
	std::string mess = _mess;
	std::string subMess = {};
	uint8_t frameQuantity = 0;
	
	idHandler();

	frameQuantity = mess.length() > (FRAME_LENGTH - FIRST_FRAME_DATA_LENGTH) ? (uint8_t)(mess.length()/ OTHER_FRAME_DATA_LENGTH) + 1 : 1;

	if(frameQuantity > UINT8_MAX){
		throw std::out_of_range("Message is to big");
	}

	for (int i = 0; i < frameQuantity; ++i) {
		subMess += idNumber;
		subMess += i;

		if (i == 0) {
			subMess += frameQuantity;
			subMess += mess.substr(0, FIRST_FRAME_DATA_LENGTH); //data for package
			mess.erase(0, FIRST_FRAME_DATA_LENGTH);
		}
		else {
			subMess += mess.substr(0, OTHER_FRAME_DATA_LENGTH); //data for package
			mess.erase(0, OTHER_FRAME_DATA_LENGTH);
		}

		subMess += checkSumCount(subMess);//checksum
		
		try{
			buffor.addLast(subMess);
		}catch(std::exception e){
			throw;
		}

		subMess.clear();
	}
}


std::string Transmiter::sendBufforElement(const int & elem) {
	std::string mess = {};
	
	try{
		mess = buffor.getElement(elem);
	}catch(std::exception e){
		throw;
	}

	return mess;
}

int Transmiter::bufforSize() const {
	return buffor.size();
}

bool Transmiter::bufforIsEmpty() const {
	return buffor.isEmpty();
}

uint8_t Transmiter::checkSumCount(const std::string &  mess) {
	uint8_t checksum = 0xFF;
	uint8_t messLength = (uint8_t)mess.length();
	uint8_t tmp = 0;

	for (int i = 1; i < messLength; ++i) {
		tmp += mess[i];
	}

	checksum -= tmp;
	return checksum;
}

void Transmiter::idHandler(){
	(idNumber + 1) == 0 ? idNumber = 1 : idNumber += 1;
}

