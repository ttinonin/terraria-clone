#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

#include <gameMain.h>

int main()
{
#if PRODUCTION_BUILD == 1
	SetTraceLogLevel(LOG_NONE);
#endif

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1280, 720, "Terraria");
	SetExitKey(KEY_NULL);
	SetTargetFPS(240);

#pragma region imgui
	rlImGuiSetup(true);

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.FontGlobalScale = 2;
#pragma endregion

	if (!initGame()) {
		return 0;
	}

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

#pragma region imgui
		rlImGuiBegin();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
#pragma endregion

		if (!updateGame()) {
			CloseWindow();
		}

		rlImGuiEnd();

		EndDrawing();
	}

	CloseWindow();

	closeGame();

	rlImGuiShutdown();

	return 0;
}