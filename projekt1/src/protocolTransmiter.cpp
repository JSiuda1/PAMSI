#include "linkedList.hh"
#include "protocolTransmiter.hh"

#include <iostream>

bool Transmiter::addMessage(const std::string & _mess) {
	std::string mess = _mess;
	std::string subMess = {};
	uint8_t packageQuantinty = 0;
	magicNumber += 1; //uint overflow

	packageQuantinty = ((mess.length() - 4) / 5) + 2;

	for (int i = 0; i < packageQuantinty; ++i) {
		subMess += magicNumber;
		subMess += i;

		if (i == 0) {
			subMess += packageQuantinty;
			subMess += mess.substr(0, 4);
			mess.erase(0, 4);
		}
		else {
			subMess += mess.substr(0, 5);
			mess.erase(0, 5);
		}

		subMess += checkSumCount(subMess);//checksum
		
		if (!buffor.push(subMess)) {
			return false;
		}
		subMess.clear();
	}

	return true;
}

//friend
std::string Transmiter::sendBuffer(const int & elem) {
	std::string mess;
	
	if (!buffor.getElement(elem, mess)) {
		throw std::exception("Get element error");
	}

	return mess;
}

int Transmiter::bufforSize() const {
	return buffor.size();
}

bool Transmiter::bufforIsEmpty() const {
	return buffor.isEmpty();
}

uint8_t Transmiter::checkSumCount(const std::string &  _mess) {
	uint8_t checksum = 0xFF;
	uint8_t messLength = _mess.length();
	uint8_t tmp = 0;

	for (int i = 1; i < messLength; ++i) {
		tmp += _mess[i];
	}

	checksum -= tmp;
	return checksum;
}