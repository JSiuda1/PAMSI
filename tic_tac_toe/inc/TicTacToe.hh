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

struct position{
  uint8_t i;
  uint8_t j;
};

class TicTacToe{
  char** board;
  uint8_t boardSize;
  uint8_t currentPlayer;
  uint8_t humanMark;
  uint8_t aiMark;

  public:
  TicTacToe(uint8_t _boardSize);
  void resizeBoard(uint8_t newBoardSize) noexcept;
  void startGame();
  uint8_t checkWin(uint8_t i, uint8_t j, uint8_t player);
  uint8_t checkWinner();
  uint8_t moveAndCheck(uint8_t i, uint8_t j);
  States getCurrentPlayer();
  //void setDepthSize(uint8_t depth);

  ~TicTacToe();
  void printBoard();
  bool humanMove(uint8_t i, uint8_t j);
  void aiMove();
  int miniMax(int depth, bool maximizingPlayer);
  int miniMaxAlphABeta(int depth, int alpha, int beta, bool maximizingPlayer);
  private:
  void clearBoard();
};