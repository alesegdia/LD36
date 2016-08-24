#include "game/ld36game.h"
#include "game/gameconfig.h"

int main(int argc, char** argv) {
	LD36 tsr(	GameConfig::WINDOW_WIDTH	* GameConfig::CAMERA_SCALE,
					GameConfig::WINDOW_HEIGHT	* GameConfig::CAMERA_SCALE	);
	tsr.exec();
	return 0;
}
