#include "gui.h"
#include <thread>
#include "TicTacToeGui.h"

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE previousInstance, PWSTR arguments,int commandShow) {
	//create gui
	gui::CreateHWindow("Cheat menu", "Cheat menu class");
	gui::CreateDevice();
	gui::CreateImGui();

	TicTacToeGui tictactoe(3);

	while (gui::exit) {

		gui::BeginRender();
		
		ImGui::SetNextWindowPos({ 0,0 });
		ImGui::SetNextWindowSize({ WINDOW_WIDTH, WINDOW_HEIGHT });
		ImGui::Begin("TicTacToe", &gui::exit,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove
		);

		tictactoe.window();

		ImGui::End();

		gui::EndRender();


		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyMHWindow();

	return EXIT_SUCCESS;
}