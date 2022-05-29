#include "TicTacToe.h"

/**
 * @brief Construct a new Tic Tac Toe:: Tic Tac Toe object
 *
 * @param _boardSize board size nxn
 */
TicTacToe::TicTacToe(uint8_t _boardSize) {
  if (_boardSize < 3 || _boardSize > MAX_BOARD_SIZE) {
    boardSize = 3;
  }
  else {
    boardSize = _boardSize;
  }

  board = new char* [boardSize];
  for (int i = 0; i < boardSize; ++i) {
    board[i] = new char[boardSize];
  }

  miniMaxDepth = 3;
  currentPlayer = X;
  humanMark = X;
  aiMark = O;
  clearBoard();
}

void TicTacToe::aiStart() {
  aiMark = X;
  humanMark = O;
}

void TicTacToe::humanStart() {
  aiMark = O;
  humanMark = X;
}

/**
 * @brief change board size
 *
 * @param newBoardSize new board size
 */
void TicTacToe::resizeBoard(uint8_t newBoardSize) noexcept {
  float previousBoardSize = boardSize;

  if (newBoardSize < 3 || newBoardSize > MAX_BOARD_SIZE) {
    boardSize = 3;
  }
  else {
    boardSize = newBoardSize;
  }

  for (int i = 0; i < previousBoardSize; ++i) {
    delete[] board[i];
  }
  delete[] board;


  board = new char* [boardSize];
  for (int i = 0; i < boardSize; ++i) {
    board[i] = new char[boardSize];
  }

  clearBoard();
}

/**
 * @brief Start game
 *
 */
void TicTacToe::startGame() {
  clearBoard();
  currentPlayer = X;

  if (aiMark == X) {
    aiMove();
  }
}

/**
 * @brief combo human and ai move with check winner
 *
 * @param i human move - horizontal position
 * @param j human move - vertical position
 * @return uint8_t game status
 */
uint8_t TicTacToe::moveAndCheck(uint8_t i, uint8_t j) {
  uint8_t status = 0;
  if (humanMove(i, j) == false) return 0;
  status = checkWinner();
  if (status != 0) return status;
  aiMoveAlphaBeta();
  status = checkWinner();

  return status;
}

/**
 * @brief User move
 *
 * @param i horizontal position
 * @param j vertical position
 * @return true move is correct
 * @return false move is incorrectin
 */
bool TicTacToe::humanMove(uint8_t i, uint8_t j) {
  if (i >= boardSize || j >= boardSize) {
    return false;
  }

  //place is occupying
  if (board[i][j] != Blank) {
    return false;
  }

  board[i][j] = currentPlayer;
  currentPlayer == X ? currentPlayer = O : currentPlayer = X;
  return true;
}

/**
 * @brief check game status
 *
 * @return uint8_t game status
 */
uint8_t TicTacToe::checkWinner() {
  uint8_t k = 0;

  //rows
  for (int i = 0; i < boardSize; ++i) {
    k = 0;
    if (board[i][0] != Blank) {
      for (int j = 1; j < boardSize; ++j) {
        if (board[i][0] == board[i][j]) {
          k++;
        }
        else {
          break;
        }
      }

      if (k == boardSize - 1) return board[i][0];
    }
  }

  //collumns
  for (int j = 0; j < boardSize; ++j) {
    k = 0;
    if (board[0][j] != Blank) {
      for (int i = 1; i < boardSize; ++i) {
        if (board[0][j] == board[i][j]) {
          k++;
        }
        else {
          break;
        }
      }

      if (k == boardSize - 1) return board[0][j];
    }
  }

  //diagonal
  k = 0;
  if (board[0][0] != Blank) {
    for (int i = 1; i < boardSize; ++i) {
      if (board[0][0] == board[i][i]) {
        k++;
      }
      else {
        break;
      }
    }
    if (k == boardSize - 1) return board[0][0];
  }

  //antidiagonal
  k = 0;
  if (board[0][boardSize - 1] != Blank) {
    for (int i = 1; i < boardSize; ++i) {
      if (board[0][boardSize - 1] == board[i][(boardSize - 1) - i]) {
        k++;
      }
      else {
        break;
      }
    }
    if (k == boardSize - 1) return board[0][boardSize - 1];
  }

  //check 
  for (int i = 0; i < boardSize; ++i) {
    for (int j = 0; j < boardSize; ++j) {
      if (board[i][j] == Blank) return Nothing;
    }
  }

  //board is filled 
  return Tie;
}

/**
 * @brief miniMax ai move
 *
 */
void TicTacToe::aiMove() {
  aiMax(miniMaxDepth);
  currentPlayer == X ? currentPlayer = O : currentPlayer = X;
}

/**
 * @brief miniMax with alpha beta ai move
 *
 */
void TicTacToe::aiMoveAlphaBeta() {
  aiMax(miniMaxDepth, INT_MIN, INT_MAX);
  currentPlayer == X ? currentPlayer = O : currentPlayer = X;
}

/**
 * @brief clear board conetent
 *
 */
void TicTacToe::clearBoard() {
  for (int i = 0; i < boardSize; ++i) {
    std::fill(board[i], board[i] + boardSize, static_cast<char>(Blank));
  }
  currentPlayer = X;
}

/**
 * @brief maximiznig move
 *
 * @param depth current depth
 * @return int best result
 */
int TicTacToe::aiMax(uint8_t depth) {
  int bestResult = INT_MIN;
  uint8_t gameResult = 0;
  int result = 0;
  uint8_t besti = 0, bestj = 0;

  gameResult = checkWinner();
  if (depth == 0 || gameResult != 0) {
    if (gameResult == aiMark) { //ai win
      return 10;
    }
    else if (gameResult == humanMark) { //human win
      return -10;
    }
    else {  //tie
      return 0;
    }
  }

  for (int i = 0; i < boardSize; ++i) {
    for (int j = 0; j < boardSize; ++j) {
      if (board[i][j] == Blank) {
        board[i][j] = aiMark;
        result = aiMin(depth - 1);
        board[i][j] = Blank;
        if (result > bestResult) {
          bestResult = result;
          besti = i;
          bestj = j;
        }
      }
    }
  }

  if (depth == miniMaxDepth) {
    board[besti][bestj] = currentPlayer;
  }
  return bestResult;
}

/**
 * @brief minimiznig move
 *
 * @param depth current depth
 * @return int best result
 */
int TicTacToe::aiMin(uint8_t depth) {
  int bestResult = INT_MAX;
  uint8_t gameResult = 0;
  int result = 0;

  gameResult = checkWinner();
  if (depth == 0 || gameResult != 0) {
    if (gameResult == aiMark) { //ai win
      return 10;
    }
    else if (gameResult == humanMark) { //human win
      return -10;
    }
    else {  //tie
      return 0;
    }
  }

  for (int i = 0; i < boardSize; ++i) {
    for (int j = 0; j < boardSize; ++j) {
      if (board[i][j] == Blank) {
        board[i][j] = humanMark;
        result = aiMax(depth - 1);
        board[i][j] = Blank;
        if (result < bestResult) {
          bestResult = result;
        }
      }
    }
  }

  return bestResult;
}

/**
 * @brief maximiznig move with alpha beta
 *
 * @param depth current depth
 * @param alpha alpha parameter
 * @param beta betha parameter
 * @return int best result
 */
int TicTacToe::aiMax(uint8_t depth, int alpha, int beta) {
  int bestResult = INT_MIN;
  uint8_t gameResult = 0;
  int result = 0;
  uint8_t besti = 0, bestj = 0;

  gameResult = checkWinner();
  if (depth == 0 || gameResult != 0) {
    if (gameResult == aiMark) { //ai win
      return 10;
    }
    else if (gameResult == humanMark) { //human win
      return -10;
    }
    else {  //tie
      return 0;
    }
  }

  for (int i = 0; i < boardSize; ++i) {
    for (int j = 0; j < boardSize; ++j) {
      if (board[i][j] == Blank) {
        board[i][j] = aiMark;
        result = aiMin(depth - 1, alpha, beta);
        board[i][j] = Blank;

        if (result > bestResult) {
          bestResult = result;
          besti = i;
          bestj = j;
        }

        if (bestResult >= beta) {
          return bestResult;
        }

        if (bestResult > alpha) {
          alpha = bestResult;
        }
      }
    }
  }

  if (depth == miniMaxDepth) {
    board[besti][bestj] = currentPlayer;
  }
  return bestResult;
}

/**
 * @brief minimiznig move with alpha beta
 *
 * @param depth current depth
 * @param alpha alpha parameter
 * @param beta betha parameter
 * @return int best result
 */
int TicTacToe::aiMin(uint8_t depth, int alpha, int beta) {
  int bestResult = INT_MAX;
  uint8_t gameResult = 0;
  int result = 0;

  gameResult = checkWinner();
  if (depth == 0 || gameResult != 0) {
    if (gameResult == aiMark) { //ai win
      return 10;
    }
    else if (gameResult == humanMark) { //human win
      return -10;
    }
    else {  //tie
      return 0;
    }
  }

  for (int i = 0; i < boardSize; ++i) {
    for (int j = 0; j < boardSize; ++j) {
      if (board[i][j] == Blank) {
        board[i][j] = humanMark;
        result = aiMax(depth - 1, alpha, beta);
        board[i][j] = Blank;

        if (result < bestResult) {
          bestResult = result;
        }

        if (bestResult <= alpha) {
          return bestResult;
        }

        if (bestResult < beta) {
          beta = bestResult;
        }

      }
    }
  }
  return bestResult;
}

/**
 * @brief Set the Depth object
 *
 * @param _depth new depth
 */
void TicTacToe::setDepth(uint8_t _depth) {
  miniMaxDepth = _depth;
}

/**
 * @brief Get the Depth object
 *
 * @return uint8_t miniMaxDepth
 */
uint8_t TicTacToe::getDepth() const {
  return miniMaxDepth;
}

/**
 * @brief Get the boardSize object
 *
 * @return uint8_t boardSize
 */
uint8_t TicTacToe::getBoardSize() const {
  return boardSize;
}

/**
 * @brief Get board Element
 *
 * @return uint8_t board
 */
uint8_t TicTacToe::getBoardElement(uint8_t i, uint8_t j) const{
  if (i >= boardSize || j >= boardSize) {
    return Blank;
  }

  return board[i][j];
}


/**
 * @brief Destroy the Tic Tac Toe:: Tic Tac Toe object
 *
 */
TicTacToe::~TicTacToe() {
  for (int i = 0; i < boardSize; ++i) {
    delete[] board[i];
  }
  delete[] board;
}


