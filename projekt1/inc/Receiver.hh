#pragma once

#include "PriorityQueue.hh"
#include <string>
#include <iostream>
#include <exception>

class Receiver{
  PriorityQueue<std::string> buffor;
	uint8_t packageQuantity;
	uint8_t idNumber;

public:
  Receiver();

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
  void showbuffor() const;

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
};