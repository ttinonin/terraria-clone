#include <iostream>
#include <raylib.h>

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "Terraria");

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);

		DrawText("My Window", 190, 200, 20, RED);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}