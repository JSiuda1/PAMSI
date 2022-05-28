#pragma once

#include <d3d9.h>
#include "TicTacToeGui.h"
#include "TicTacToe.h"

namespace gui {

	constexpr int WIDTH = 300;
	constexpr int HEIGHT = 300;

	inline bool exit = true;

	// winapi window variables
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = {};

	// points for window movement
	inline POINTS position = {};

	// direct x state variables
	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = {};

	//handle window creation and destruction
	void CreateHWindow(const char* windowName, const char* className) noexcept;
	void DestroyMHWindow() noexcept;

	//handel device creation and destruction
	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	// handle ImGui creation and destruction
	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;
	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;

}