#pragma once

#include <string>
#include <stdint.h>
#include <PriorityQueue.hh>

#define FRAME_SIZE 8

struct ProtocolPackage {
	std::string data;
	uint8_t position;

	ProtocolPackage() = default;
	ProtocolPackage(std::string _data, uint8_t _position) :
		data(_data), position(_position) {};
};

class Receiver {
	PriorityQueue<std::string> buffor;
	uint8_t packageQuantity;
	uint8_t idNumber;

public:

	Receiver();
	bool AddPackage(const std::string& dataFrame);
	bool allFrameReceived();
	std::string getMessage();
	void showBuffor();

private:
	bool checkSumCorrect(const std::string& data, const uint8_t& checksum);
	ProtocolPackage parseDataFrame(const std::string& dataFrame);
};