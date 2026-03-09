#pragma once
#include <raylib.h>

struct AssetManager {
	Texture dirt = {};
	Texture textures = {};

	void loadAll();
};
