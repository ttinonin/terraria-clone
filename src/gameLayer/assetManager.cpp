#include "assetManager.h"

void AssetManager::loadAll() {
	dirt = LoadTexture(RESOURCES_PATH "dirt.png");
	frame = LoadTexture(RESOURCES_PATH "frame.png");

	textures = LoadTexture(RESOURCES_PATH "textures.png");
}