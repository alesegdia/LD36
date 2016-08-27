
#include "isometrictranslator.h"

Vec2i get_tile_at_iso( const Vec2i& iso )
{
	// unscale from camera & fix
	constexpr int CameraScale = 4;
	Vec2i scaled_pos = iso;
	scaled_pos.x(iso.x() / CameraScale - 32);
	scaled_pos.y(iso.y() / CameraScale + 8);

	// iso to ortho and convert to tile
	constexpr int TileSize = 32;
	Vec2i ortho = iso_to_ortho(scaled_pos);
	ortho.set( ortho.x() / TileSize, ortho.y() / TileSize);
	ortho.y(ortho.y() - 1);

	return ortho;
}
