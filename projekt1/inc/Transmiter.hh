#pragma once 

#include "linkedList.hh"
#include <string>
#include <iostream>
#include <exception>


#define FRAME_LENGTH 8
#define FIRST_FRAME_DATA_LENGTH (FRAME_LENGTH - 4)
#define OTHER_FRAME_DATA_LENGTH (FRAME_LENGTH - 3)

class Transmiter{
  LinkedList<std::string> buffor;
	uint8_t idNumber;

public:
  Transmiter();
  /**
   * @brief dodanie wiadomosci do buffora tx
   * 
   * @param _mess wiadomosc
   */
	void addMessageToBuffor(const std::string & _mess);
  /**
   * @brief zwraca wybrany element buffora tx
   * 
   * @param elem numer elementu
   * @return std::string paczka
   */
	std::string sendBufforElement(const int& elem);
	
  /**
   * @brief zwraca ilosc elementow znajdujacych sie na bufforze tx
   * 
   * @return int ilosc elementow
   */
  int bufforSize() const;

  /**
   * @brief sprawdza czy buffor tx jest pusty
   * 
   * @return true buffor pusty
   * @return false elementy sa na bufforze
   */
	bool bufforIsEmpty() const;

private:
    /**
   * @brief obliczenie checksumy 
   * 
   * @param mess wiadomość
   * @return uint8_t checksuma
   */
  uint8_t checkSumCount(const std::string & mess);
	
  /**
   * @brief ustawia odpowiednie ID
   * 
   */
  void idHandler();
};  