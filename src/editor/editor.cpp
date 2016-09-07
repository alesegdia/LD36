#include "../core/gameconfig.h"
#include "../core/ld36game.h"

int main(int argc, char** argv) {
	LD36 tsr(	GameConfig::WINDOW_WIDTH	* GameConfig::CAMERA_SCALE,
				GameConfig::WINDOW_HEIGHT	* GameConfig::CAMERA_SCALE, true	);
	tsr.exec(argc, argv);
	return 0;
}
