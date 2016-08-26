#include "assets.h"
#include <iostream>


Assets* Assets::instance = nullptr;

Assets::Assets()
{
	tilesetBitmap = al_load_bitmap("assets/tileset.png");
	tilesetSheet.reset(new Spritesheet(2, 2, tilesetBitmap));
	mapTiles = tilesetSheet->getAllFrames();
}

Assets::~Assets()
{
	// FREE RESOURCES!!
	al_destroy_bitmap(tilesetBitmap);
}

void Assets::Initialize()
{
	Assets::instance = new Assets();
}

void Assets::Dispose()
{
	delete instance;
}
