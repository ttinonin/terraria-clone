#include <raylib.h>
#include <assetManager.h>
#include "gameMain.h"
#include "helpers.h"
#include <gameMap.h>
#include <raymath.h>

struct GameData {
	GameMap gameMap;
	Camera2D camera = {};
	std::uint16_t selectedBlock;
}gameData;

AssetManager assetManager;

bool initGame() {
	assetManager.loadAll();
	
	gameData.gameMap.create(30, 10);

	gameData.gameMap.getBlockUnsafe(0, 0).type = Block::dirt;
	gameData.gameMap.getBlockUnsafe(1, 1).type = Block::grass;
	gameData.gameMap.getBlockUnsafe(2, 2).type = Block::goldBlock;
	gameData.gameMap.getBlockUnsafe(3, 3).type = Block::glass;
	gameData.gameMap.getBlockUnsafe(4, 4).type = Block::boneChest;
	
	gameData.camera.target = { 0, 0 };
	gameData.camera.rotation = 0.0f;
	gameData.camera.zoom = 100.0f;

	return true;
}

bool updateGame() {
	float deltaTime = GetFrameTime();
	if (deltaTime > 1.f / 5) { deltaTime = 1 / 5.f; }

	gameData.camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

	ClearBackground({ 75, 75, 150, 255 });

#pragma region camera movement
	if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= 7.f * deltaTime;
	if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += 7.f * deltaTime;
	if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= 7.f * deltaTime;
	if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += 7.f * deltaTime;
#pragma endregion

	Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
	int blockX = (int)floor(worldPos.x);
	int blocky = (int)floor(worldPos.y);

	if (IsKeyPressed(KEY_ONE)) {
		gameData.selectedBlock = Block::grassBlock;
	}
	if (IsKeyPressed(KEY_TWO)) {
		gameData.selectedBlock = Block::dirt;
	}
	if (IsKeyPressed(KEY_THREE)) {
		gameData.selectedBlock = Block::snow;
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		auto b = gameData.gameMap.getBlockSafe(blockX, blocky);
		if (b) {
			*b = {};
		}
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		auto b = gameData.gameMap.getBlockSafe(blockX, blocky);
		if (b) {
			b->type = gameData.selectedBlock;
		}
	}

	BeginMode2D(gameData.camera);

	Vector2 topLeftView = GetScreenToWorld2D({ 0, 0 }, gameData.camera);
	Vector2 bottomRightView = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, gameData.camera);

	int startXView = (int)floorf(topLeftView.x - 1);
	int endXView = (int)ceilf(bottomRightView.x + 1);
	int startYView = (int)floorf(topLeftView.y - 1);
	int endYView = (int)ceilf(bottomRightView.y + 1);

	startXView = Clamp(startXView, 0, gameData.gameMap.w - 1);
	endXView = Clamp(endXView, 0, gameData.gameMap.w - 1);

	startYView = Clamp(startYView, 0, gameData.gameMap.h - 1);
	endYView = Clamp(endYView, 0, gameData.gameMap.h - 1);

	for (int y = startYView; y <= endYView; y++) {
		for (int x = startXView; x <= endXView; x++) {
			auto& b = gameData.gameMap.getBlockUnsafe(x, y);

			if (b.type != Block::air) {
				DrawTexturePro(
					assetManager.textures,
					getTextureAtlas(b.type, 0, 32, 32),
					{(float)x, (float)y, 1, 1},
					{0, 0},
					0.0f,
					WHITE
				);
			}
		}
	}

	DrawTexturePro(
		assetManager.frame,
		{0,0, (float)assetManager.frame.width, (float)assetManager.frame.height},
		{(float)blockX, (float)blocky, 1, 1},
		{0,0},
		0.0f,
		WHITE
	);

	EndMode2D();

	return true;
}

void closeGame() {

}