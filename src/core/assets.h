#pragma once

#include <memory>

#include <allegro5/allegro.h>
#include <alligator/graphics/spritesheet.h>
#include <alligator/graphics/animation.h>
#include <alligator/audio/audiosample.h>
#include <alligator/audio/audiostream.h>

class Assets
{
public:

	// singleton interface
	static Assets* instance;
	static void Initialize();
	static void Dispose();

	Assets();
	~Assets();

	ALLEGRO_BITMAP* tilesetBitmap;
	ALLEGRO_BITMAP* charactersBitmap;
	ALLEGRO_BITMAP* objectsBitmap;

	Spritesheet::SharedPtr tilesetSheet;
	Spritesheet::SharedPtr charactersSheet;
	Spritesheet::SharedPtr objectsSheet;

	std::vector<ALLEGRO_BITMAP*> mapTiles;

};
