#pragma once

#include <iostream>
#include <bits/stdc++.h>

#define MAX_BOARD_SIZE 10

enum States{
  Nothing = 0x00,
  Blank = 0x20,
  Tie = 0x01,
  X = 0x58,
  O = 0x4F
};

class TicTacToe{
  char** board;
  uint8_t boardSize;
  uint8_t humanMark;
  uint8_t aiMark;
  uint8_t miniMaxDepth;

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
  
  ~TicTacToe();

  private:
  int max(uint8_t depth);
  int min(uint8_t depth);
  int max(uint8_t depth, int alpha, int beta);
  int min(uint8_t depth, int alpha, int beta);
  
  void clearBoard();
};