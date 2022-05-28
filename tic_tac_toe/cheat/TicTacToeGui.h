#pragma once

#include <stdint.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

#include <stdlib.h> 
#include "TicTacToe.h"

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300
#define BOARD_WINDOW_WIDTH WINDOW_WIDTH
#define MARGIN_SIZE 50.0f
#define TOP_MARGIN 75.0f
#define SPACER 5.0f
constexpr float boardWidth = BOARD_WINDOW_WIDTH - MARGIN_SIZE * 2;

enum class AiType : int {
	MiniMax = 0,
	MiniMaxAlphaBeta,
	Human
};

class TicTacToeGui{
	TicTacToe ttt;
	uint8_t status;
	AiType aiType;

public:
	TicTacToeGui(uint8_t boardSize);
	void window();
	void options();
	void createBoard();
	//void startGame();
};
