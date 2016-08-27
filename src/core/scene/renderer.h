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

	MapRenderer(Matrix2Di::SharedPtr map, int ext = 3);

	virtual void center(float x, float y)
	{
		m_center.set(x, y);
	}

	virtual void render();

	virtual void renderCell( int x, int y, int cell_value ) = 0 ;

	bool isVisibleTile( int x, int y )
	{
		if( x < 0 || x > m_map->cols() || y < 0 || y > m_map->rows() )
		{
			return false;
		}
		return m_visible->get(x, y) == 1;
	}

	Matrix2Di::SharedPtr getVisible()
	{
		return m_visible;
	}

protected:
	void setExt(int newext)
	{
		ext = newext;
	}

	Matrix2Di::SharedPtr m_map;
	Vec2f m_center;
	Matrix2Di::SharedPtr m_visible;
	int ext;

};

class DebugMapRenderer : public MapRenderer
{
public:
	DebugMapRenderer( Matrix2Di::SharedPtr map, int ext = 3 );

	void renderCell(int x, int y, int cell_value) override;

private:
	float m_scale = 1;

};


class FilteredDebugMapRenderer : public MapRenderer
{
public:
	typedef std::shared_ptr<FilteredDebugMapRenderer> SharedPtr;
	FilteredDebugMapRenderer( Matrix2Di::SharedPtr map, Matrix2Di::SharedPtr visited, int ext = 3 );

	void renderCell(int x, int y, int cell_value) final;

	int width()
	{
		return m_map->cols() * m_scale;
	}

	int height()
	{
		return m_map->rows() * m_scale;
	}

private:
	float m_scale = 1;
	Matrix2Di::SharedPtr m_levisible;

};


class TileMapRenderer : public MapRenderer
{
public:
	TileMapRenderer( Matrix2Di::SharedPtr map, std::vector<ALLEGRO_BITMAP*> tiles);

	void renderCell(int x, int y, int cell_value) override;

protected:
	std::vector<ALLEGRO_BITMAP*> m_tiles;

};

class IsometricTileMapRenderer : public TileMapRenderer
{
public:
	typedef std::shared_ptr<IsometricTileMapRenderer> SharedPtr;
	IsometricTileMapRenderer( Matrix2Di::SharedPtr map, std::vector<ALLEGRO_BITMAP*> tiles, size_t tile_height )
		: TileMapRenderer(map, tiles), m_tileHeight(tile_height)
	{
		setExt(1000);
	}


	void renderCell( int x, int y, int cell_value ) override
	{
		float ortho_x, ortho_y;

		ortho_x = (x * m_tileHeight) / 2;
		ortho_y = (y * m_tileHeight) / 2;

		Vec2i iso = ortho_to_iso(Vec2i(ortho_x, ortho_y));
		al_draw_bitmap(	m_tiles[cell_value], iso.x(), iso.y(), 0 );
	}

	Vec2i getTileAtIso( const Vec2i& vec )
	{
		return get_tile_at_iso(vec);
	}

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

private:
	float m_tileHeight;

};
