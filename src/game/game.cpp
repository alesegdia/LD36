#include "../core/ld36game.h"
#include "../core/gameconfig.h"

int main(int argc, char** argv) {
	LD36 tsr(	GameConfig::WINDOW_WIDTH	* GameConfig::CAMERA_SCALE,
				GameConfig::WINDOW_HEIGHT	* GameConfig::CAMERA_SCALE, true, true );
	tsr.exec(argc, argv);
	return 0;
}
