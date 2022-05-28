#include "TicTacToe.hh"

TicTacToe::TicTacToe(uint8_t _boardSize){
  if(_boardSize < 3 || _boardSize > MAX_BOARD_SIZE){
    boardSize = 3;
  }else{
    boardSize = _boardSize;
  }

  board = new char*[boardSize];
  for(int i = 0; i < boardSize; ++i){
    board[i] = new char[boardSize];
  }

  currentPlayer = X;
  humanMark = X;
  aiMark = O;
  clearBoard();
}

void TicTacToe::resizeBoard(uint8_t newBoardSize) noexcept{
  float previousBoardSize = boardSize;

  if(newBoardSize < 3 || newBoardSize > MAX_BOARD_SIZE){
    boardSize = 3;
  }else{
    boardSize = newBoardSize;
  }
  
  for(int i = 0; i < previousBoardSize; ++i){
    delete[] board[i];
  }
  delete[] board;


  board = new char*[boardSize];
  for(int i = 0; i < boardSize; ++i){
    board[i] = new char[boardSize];
  }
  
  clearBoard();
}

void TicTacToe::printBoard(){
  for(int i = 0; i < boardSize; ++i){
    for(int j = 0; j < boardSize - 1; ++j){
      std::cout << " " << board[i][j] << " |";
    }
    std::cout << " " << board[i][boardSize-1] << "\n";

    if(boardSize - 1 != i){
      for(int k = 0; k < boardSize*3; ++k){
        std::cout << "-";
      }
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void TicTacToe::startGame(){
  clearBoard();
  if(aiMark == X){
    //aiMove();
  }
}

uint8_t TicTacToe::moveAndCheck(uint8_t i, uint8_t j){
  /*
  uint8_t status = 0;
  uint8_t aiPoss = 0;
  if(humanMove(i, j)==false) return 0;
  status = checkWin(i, j, humanMark);
  printBoard();
  if(status != 0) return status;
  //aiPoss = aiMove();
  status = checkWin(aiPoss/10, j%10, aiMark);
  */

  uint8_t status = 0;
  if(humanMove(i, j)==false) return 0;
  status = checkWinner();
  if(status != 0) return status;
  aiMove();
  status = checkWinner();

  return status;
}

bool TicTacToe::humanMove(uint8_t i, uint8_t j){
  if(i >= boardSize || j >= boardSize){
    return false;
  }

  //place is occupying
  if(board[i][j] != Blank){
    return false;
  }

  board[i][j] = humanMark;
  return true;
}

uint8_t TicTacToe::checkWinner(){
  uint8_t k = 0;

  //rows
  for(int i =0; i < boardSize; ++i){
    k = 0;
    if(board[i][0] != Blank){
      for(int j = 1; j < boardSize; ++j){
        if(board[i][0] == board[i][j]){
          k++;
        }else{
          break;
        }
      }

      if(k == boardSize - 1) return board[i][0];
    }
  }

  //collumns
  for(int j =0; j < boardSize; ++j){
    k = 0;
    if(board[0][j] != Blank){
      for(int i = 1; i < boardSize; ++i){
        if(board[0][j] == board[i][j]){
          k++;
        }else{
          break;
        }
      }

      if(k == boardSize - 1) return board[0][j];
    }
  }

  //diagonal
  k = 0;
  if(board[0][0] != Blank){
    for(int i = 1; i < boardSize; ++i){
      if(board[0][0] == board[i][i]){
        k++;
      }else{
        break;
      } 
    }
    if(k == boardSize - 1) return board[0][0];
  }

  //antidiagonal
  k = 0;
  if(board[0][boardSize - 1] != Blank){
    for(int i = 1; i < boardSize; ++i){
      if(board[0][boardSize - 1] == board[i][(boardSize - 1) - i]){
        k++;
      }else{
        break;
      } 
    }
    if(k == boardSize - 1) return board[0][boardSize - 1];
  }

  //check 
  for(int i = 0; i < boardSize; ++i){
    for(int j = 0; j < boardSize; ++j){
      if(board[i][j] == Blank) return Nothing;
    }
  }

  //board is filled 
  return Tie;
}

uint8_t TicTacToe::checkWin(uint8_t i, uint8_t j, uint8_t player){
  int sum = 0;

  //collumn
  for(int k=0; k < boardSize; ++k){
    sum += board[i][k]; 
  }

  if(sum == player*boardSize) return player;

  //row 
  sum = 0;
  for(int k=0; k < boardSize; ++k){
    sum += board[k][j]; 
  }

  if(sum == player*boardSize) return player;

  //check diagonal
  sum = 0;
  if(i == j){
    for(int k =0; k < boardSize; ++k){
      sum += board[k][k];
    }
  }

  if(sum == player*boardSize) return player;

  //chack anti diagonal
  sum = 0;
  if(i + j == boardSize - 1){
    for(int k =0; k < boardSize; ++k){
      sum += board[k][(boardSize-1) - k];
    }
  }
  if(sum == player*boardSize) return player;
  
  //check if board is filled out
  for(int i=0; i < boardSize; ++i){
    for(int j=0; j < boardSize; ++j){
      if(board[i][j] == Blank) return 0; //game is still
    }
  }

  return Tie;
}

void TicTacToe::aiMove(){
  int bestResult = INT_MIN;
  int result = 0;
  uint8_t besti = 0, bestj = 0;
  
  for(int i =0; i < boardSize; ++i){
    for(int j = 0; j < boardSize; ++j){
      if(board[i][j] == Blank){
        board[i][j] = aiMark;
        result = miniMaxAlphABeta(4, -INT_MAX, INT_MAX, false);
        board[i][j] = Blank;
        if(result > bestResult){
          bestResult = result;
          besti = i;
          bestj = j;
        }
      }
    }
  }

  board[besti][bestj] = aiMark;
}

int TicTacToe::miniMax(int depth, bool maximizingPlayer){
  uint8_t gameResult = checkWinner();
  int result = 0;

  if(depth == 0 || gameResult != 0){
    if(gameResult == aiMark){
      return 10;
    }else if(gameResult == humanMark){
      return -10;
    }else{
      return 0;
    }
  }

  if(maximizingPlayer){
    int bestResult = INT_MIN;
    for(int i = 0; i < boardSize; ++i){
      for(int j = 0; j < boardSize; ++j){
        if(board[i][j] == Blank){
          board[i][j] = aiMark;
          result = miniMax(depth - 1, false);
          board[i][j] = Blank;
          if(result > bestResult){
            bestResult = result;
          }
        }
      }
    }
    return bestResult;
  }else{
    int bestResult = INT_MAX;
    for(int i = 0; i < boardSize; ++i){
      for(int j = 0; j < boardSize; ++j){
        if(board[i][j] == Blank){
          board[i][j] = humanMark;
          result = miniMax(depth - 1, true);
          board[i][j] = Blank;
          if(result < bestResult){
            bestResult = result;
          }
        }
      }
    }
    return bestResult;
  }
}

int TicTacToe::miniMaxAlphABeta(int depth, int alpha, int beta, bool maximizingPlayer){
  uint8_t gameResult = checkWinner();
  int result = 0;

  if(depth == 0 || gameResult != 0){
    if(gameResult == aiMark){
      return 10;
    }else if(gameResult == humanMark){
      return -10;
    }else{
      return 0;
    }
  }

  if(maximizingPlayer){
    int bestResult = INT_MIN;
    for(int i = 0; i < boardSize; ++i){
      for(int j = 0; j < boardSize; ++j){
        if(board[i][j] == Blank){
          board[i][j] = aiMark;
          result = miniMax(depth - 1, false);
          board[i][j] = Blank;
          if(result > bestResult){
            bestResult = result;
          }

          if(bestResult >= beta){
            return bestResult;
          }

          if(bestResult > alpha){
            alpha = bestResult;
          }
        }
      }
    }
    return bestResult;
  }else{
    int bestResult = INT_MAX;
    for(int i = 0; i < boardSize; ++i){
      for(int j = 0; j < boardSize; ++j){
        if(board[i][j] == Blank){
          board[i][j] = humanMark;
          result = miniMax(depth - 1, true);
          board[i][j] = Blank;
          if(result < bestResult){
            bestResult = result;
          }

          if(bestResult <= alpha){
            return bestResult;
          }

          if(bestResult < beta){
            beta = bestResult;
          }
        }
      }
    }
    return bestResult;
  }
}

States TicTacToe::getCurrentPlayer(){
  return static_cast<States>(currentPlayer);
}

void TicTacToe::clearBoard(){
  for(int i = 0; i < boardSize; ++i){
    std::fill(board[i], board[i] + boardSize, static_cast<char>(Blank));
  }

  //currentPlayer = X;
}

TicTacToe::~TicTacToe(){
  for(int i = 0; i < boardSize; ++i){
    delete[] board[i];
  }
  delete[] board;
}