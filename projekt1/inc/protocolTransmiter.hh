#pragma once

#include "linkedList.hh"
#include <string>

#define FRAME_SIZE 8

class Transmiter {
	LinkedList<std::string> buffor;
	uint8_t magicNumber;

public:
	Transmiter() = default;
	bool addMessage(const std::string & _mess);
	std::string sendBuffer(const int& elem);
	int bufforSize() const;
	bool bufforIsEmpty() const;

private:
	uint8_t checkSumCount(const std::string & _mess);
};