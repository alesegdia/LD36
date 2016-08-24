#include "ld36game.h"
#include "assets.h"

#include <allegro5/allegro_ttf.h>

#include "gameconfig.h"

LD36::LD36(int sw, int sh)
	: Game( sw, sh ), m_camera1(Vec2f(sw, sh)), m_camera2(Vec2f(sw, sh)), m_camera3(Vec2f(sw, sh))
{

}

LD36::~LD36()
{

}

void LD36::create()
{
	Assets::Initialize();

	m_camera1.scale(GameConfig::CAMERA_SCALE, GameConfig::CAMERA_SCALE);
	m_camera2.scale(GameConfig::CAMERA_SCALE, GameConfig::CAMERA_SCALE);
	m_camera3.scale(GameConfig::CAMERA_SCALE, GameConfig::CAMERA_SCALE);

	m_font = al_load_ttf_font("assets/dafont.ttf", 8, 0);
	m_fontBig = al_load_ttf_font("assets/dafont.ttf", 16, 0);
	if( !m_font )
	{
		fprintf(stderr, "Failed to load font!\n");
	}

	m_menuScreen.reset(new MenuScreen(this));

	setScreen(m_menuScreen);
}

void LD36::dispose()
{
	Assets::Dispose();
	m_menuScreen.reset();
	al_destroy_font(m_font);
	al_destroy_font(m_fontBig);
}

void LD36::update(double delta)
{

	if( Input::IsKeyJustPressed(ALLEGRO_KEY_F1) )
	{
		setScreen(m_menuScreen);
	}

	if( Input::IsKeyJustPressed(ALLEGRO_KEY_ESCAPE) )
	{
		Game::close();
		close();
	}

	Game::update(delta);
}

