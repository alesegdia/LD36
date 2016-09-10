#pragma once

#include <memory>
#include <list>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <alligator/util/matrix.h>
#include <alligator/util/math.h>

#include "isometrictranslator.h"

class MapRenderer
{
public:
	typedef std::shared_ptr<MapRenderer> SharedPtr;

	MapRenderer(Matrix2Di::SharedPtr map, std::vector<ALLEGRO_BITMAP *> tiles, float tileHeight);

	void render();


protected:
	Matrix2Di::SharedPtr m_map;
	std::vector<ALLEGRO_BITMAP *> m_tiles;
	float m_tileHeight;

};



	/*
	void render() override
	{
		int max_dimension = std::max(m_map->cols(), m_map->rows());
		int min_dimension = std::min(m_map->cols(), m_map->rows());
		for( int d = 0; d < max_dimension; d++ )
		{
			int cell_value;
			int loop_limit = std::min(d, min_dimension);
			int c1 = 0;
			int c2 = loop_limit - 1;
			for( int tt = 0; tt < loop_limit; tt++ )
			{

				float x, y;
				if( max_dimension == m_map->cols() )
				{
					x = c1; y = c2;
				}
				else
				{
					x = c2; y = c1;
				}
				cell_value = m_map->get(x, y);
				x *= m_tileHeight;
				y *= m_tileHeight;
				float dum = std::abs(float(m_map->cols()/2)*m_tileHeight + float(d) * m_tileHeight);

				x = (x - y) + dum;
				y = (x + y) / 2.f;

				//x = x * (m_tileHeight * 2);
				//y = y * (m_tileHeight);
				al_draw_bitmap( m_tiles[cell_value], x, y, 0 );
				c1++;
				c2--;
			}
		}
		printf("\n\n");

	}
*/
