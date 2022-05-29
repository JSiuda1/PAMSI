#include "TicTacToeGui.h"
#include "TicTacToe.h"

TicTacToeGui::TicTacToeGui(uint8_t boardSize) :
	ttt(TicTacToe(boardSize)),
	status(0),
	aiType(AiType::MiniMax)
{}

void  TicTacToeGui::window() {
	if (ImGui::BeginTabBar("TicTacToe")) {
		if (ImGui::BeginTabItem("Game")) {
			if (status != 0){
				if (status != Tie) {
					ImGui::Text("%c WIN", status);
				}
				else {
					ImGui::Text("DRAW");
				}
				ImGui::SameLine();
				ImGui::Button("Play again");
				if (ImGui::IsItemClicked()) {
					startGame();
				}
			}
			else {
				ImGui::Text("");
			}
				createBoard();

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Options")) {
			options();
			ImGui::EndTabItem();
		}
	}
}

void TicTacToeGui::options() {
	//slider
	static int depth = ttt.getDepth();
	static int maxDepth = 20;

	//combo box board size
	static ImGuiComboFlags sizeFlags = 0;
	const char* items[] = { "3", "4", "5", "6", "7" };
	static int selectedSize = 0;
	const char* previewSize = items[selectedSize];

	//combo box ai type
	static ImGuiComboFlags aiFlags = 0;
	const char* itemsAi[] = { "MiniMax", "MiniMaxAlphaBeta", "Human" };
	static int selectedAi = 0;
	const char* previewAi = itemsAi[selectedAi];
	
	//check box
	static bool aiStart = false;
	static bool previousAiStart = false;

	ImGui::SliderInt("depth", &depth, 1, maxDepth);
	ttt.setDepth(depth);

	//size combo box
	if (ImGui::BeginCombo("Size", previewSize, sizeFlags))
	{
		for (int i = 0; i < IM_ARRAYSIZE(items); ++i)
		{
			const bool is_selected = (selectedSize == i);
			if (ImGui::Selectable(items[i], is_selected)) {
				selectedSize = i;
				ttt.resizeBoard(atoi(items[selectedSize]));
				
				if (selectedSize > 0) { //if boardsize is greather than 3 decrease depth size
					maxDepth = 5;
					ttt.setDepth(3);
				}
				else {
					maxDepth = 10;
				}

				startGame();
			}
		}
		ImGui::EndCombo();
	}
	
	//ai combo box
	if (ImGui::BeginCombo("Opponent type", previewAi, aiFlags))
	{
		for (int i = 0; i < IM_ARRAYSIZE(itemsAi); ++i)
		{
			const bool is_selected = (selectedAi == i);
			if (ImGui::Selectable(itemsAi[i], is_selected)) {
				selectedAi = i;
				aiType = static_cast<AiType>(i);

				//disable ai start
				if (aiType == AiType::Human) {
					aiStart = false;
					ttt.humanStart();
				}

				startGame();
			}
		}
		ImGui::EndCombo();
	}

	if (aiType != AiType::Human) {
		ImGui::Checkbox("AI start", &aiStart);
		if (aiStart != previousAiStart) {
			if (aiStart) {
				ttt.aiStart();
			}
			else {
				ttt.humanStart();
			}
			previousAiStart = aiStart;
			startGame();
		}
	}
}

void TicTacToeGui::createBoard() {
	char text[3];
	int boardSize = ttt.getBoardSize();
	float buttonSize = (boardWidth - SPACER * (boardSize - 1)) / boardSize;
	float cursorPositionY = 0;

	ImGui::SetCursorPos({ MARGIN_SIZE, TOP_MARGIN });

	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			sprintf_s(text, "%c", ttt.getBoardElement(i, j));
			ImGui::Button(text, {buttonSize, buttonSize});
			
			if (ImGui::IsItemClicked()) {
				if (status == 0) { //if game is still going
					if (ttt.humanMove(i, j)) { //if human move is correct
						status = ttt.checkWinner();
						
						if (status == 0) { //if game is still going
							if (aiType == AiType::MiniMax) { //ai mmove
								ttt.aiMove();
							}
							else if (aiType == AiType::MiniMaxAlphaBeta) {
								ttt.aiMoveAlphaBeta();
							}

							status = ttt.checkWinner();
						}
					}
				}
			}

			if (j != boardSize - 1) {
				ImGui::SameLine(0, SPACER);
			}
		}

		cursorPositionY = TOP_MARGIN + (buttonSize + SPACER) * (i + 1);
		ImGui::SetCursorPos({ MARGIN_SIZE, cursorPositionY });
	}
}


void TicTacToeGui::startGame() {
	ttt.startGame();
	status = 0;
}
/*
bool optionsScreen() {
	ImGui::Columns(2);
	//board
	ImGui::SetColumnWidth(0, BOARD_WINDOW_WIDTH);
	static int boardSize = 3;
	createBoard(boardSize);


	//options box
	ImGui::NextColumn();
	ImGui::SetWindowPos({ 10, 10 });
	ImGui::Text("Options");

	//depth slider
	static int depth = 10; 
	static const char* sizes = {"3\0 4\0"};
	ImGui::SliderInt("depth", &depth, 0, 100);

	//size combo box
	static ImGuiComboFlags flags = 0;
	const char* items[] = { "3", "4", "5", "6", "7" };
	static int selectedSize = 0;
	const char* preview = items[selectedSize];  
	if (ImGui::BeginCombo("Size", preview, flags))
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		{
			const bool is_selected = (selectedSize == n);
			if (ImGui::Selectable(items[n], is_selected)){
				selectedSize = n;
				boardSize = atoi(items[selectedSize]);
			}
		}
		ImGui::EndCombo();
	}

	ImGui::Button("START");
	if (ImGui::IsItemClicked) {
		return true;
	}
}
*/