#include <iostream>

#include "TicTacToe.hh"

int main(){
  TicTacToe ttt(3);
  uint8_t status = 0;
  uint8_t x = 0;
  uint8_t y = 0;

  ttt.startGame();
  
  while(status == 0){
    std::cin >> x;
    std::cin >> y;
    status = ttt.moveAndCheck(x - 48, y - 48);
    ttt.printBoard();
  }
  /*
  ttt.moveAndCheck(2, 0);
  status = ttt.checkWinner();
  ttt.printBoard();

  
   std::cout << "Status " << static_cast<char>(status) << "\n";


  ttt.moveAndCheck(1, 1);
  status = ttt.checkWinner();
  ttt.printBoard();

  
   std::cout << "Status " << static_cast<char>(status) << "\n";


  ttt.moveAndCheck(0, 2);
  status = ttt.checkWinner();
  ttt.printBoard();

   std::cout << "Status " << static_cast<char>(status) << "\n";
  */
}
