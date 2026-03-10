#pragma once
#include <raylib.h>

struct AssetManager {
	Texture dirt = {};
	Texture frame = {};
	Texture textures = {};

	void loadAll();
};
