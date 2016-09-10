#include "renderer.h"

MapRenderer::MapRenderer(Matrix2Di::SharedPtr map, std::vector<ALLEGRO_BITMAP *> tiles, float tileHeight )
	: m_map(map), m_tiles(tiles), m_tileHeight(tileHeight)
{

}

void MapRenderer::render()
{
	for( int y = 0; y < m_map->rows(); y++ )
	{
		for( int x = 0; x < m_map->cols(); x++ )
		{
			if( x >= 0 && x < m_map->cols() &&
				y >= 0 && y < m_map->rows())
			{

				float ortho_x, ortho_y;

				ortho_x = (x * m_tileHeight) / 2;
				ortho_y = (y * m_tileHeight) / 2;

				Vec2i iso = ortho_to_iso(Vec2i(ortho_x, ortho_y));
				al_draw_bitmap(	m_tiles[m_map->get(x, y)], iso.x(), iso.y(), 0 );
			}
		}
	}
}


