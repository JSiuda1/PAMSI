#pragma once

#include <iostream>
#include <Bits.h>

#define MAX_BOARD_SIZE 10

enum States {
  Nothing = 0x00,
  Blank = 0x20,
  Tie = 0x01,
  X = 0x58,
  O = 0x4F
};

class TicTacToe {
  char** board;
  uint8_t boardSize;
  uint8_t miniMaxDepth;
  uint8_t currentPlayer;
  uint8_t aiMark;
  uint8_t humanMark;

public:
  TicTacToe(uint8_t _boardSize);
  void resizeBoard(uint8_t newBoardSize) noexcept;
  void startGame();
  uint8_t checkWinner();
  uint8_t moveAndCheck(uint8_t i, uint8_t j);
  //uint8_t checkWin(uint8_t i, uint8_t j, uint8_t player);
  void printBoard();
  bool humanMove(uint8_t i, uint8_t j);
  void aiMove();
  void aiMoveAlphaBeta();
  void setDepth(uint8_t _depth);
  uint8_t getDepth() const;
  uint8_t getBoardSize() const;
  uint8_t getBoardElement(uint8_t i, uint8_t j) const;
  void clearBoard();
  void aiStart();
  void humanStart();

  ~TicTacToe();

private:
  int aiMax(uint8_t depth);
  int aiMin(uint8_t depth);
  int aiMax(uint8_t depth, int alpha, int beta);
  int aiMin(uint8_t depth, int alpha, int beta);

};