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
  /**
   * @brief dodanie odebranej ramki do buffora
   * 
   * @param dataFrame ramka
   */
	void AddPackage(const std::string& dataFrame);
  
  /**
   * @brief sprawdzenie czy wszyskie ramki przyszły
   * 
   * @return true wszystkie ramki odebrane
   * @return false nie ma wszystkich ramek
   */
  bool allFrameReceived();
  
  /**
   * @brief zwraca odebraną wiadomosc
   * 
   * @return std::string wiadomosc
   */
	std::string getMessage();
	
  /**
   * @brief Wypisanie w konsoli elementow buffora rx tylko do pokazania dzialania programu
   * 
   */
  void showRxBuffor() const;
  
  //transmit
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
	std::string sendBufferElement(const int& elem);
	
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
  //receive
  /**
   * @brief sprawdza poprawnosc checksumy
   * 
   * @param data ramka danych
   * @param checksum poprawna checksuma
   * @return true checksuma poprawna 
   * @return false checksuma niepoprawna ramka uszkodzona
   */
	bool checkSumCorrect(const std::string& data, const uint8_t& checksum);
	
  /**
	 * @brief rozkłada odebrana ramke 
	 * 
	 * @param dataFrame ramka
	 * @param dataOutput wyciagniete dane
	 * @param priority numer ramki
	 */
  void parseDataFrame(const std::string& dataFrame, std::string & dataOutput, uint8_t & priority);
  /**
   * @brief czyszczenie sekcji receive
   * 
   */
	void clear();

	//transmit
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
  void idTxHandler();

};