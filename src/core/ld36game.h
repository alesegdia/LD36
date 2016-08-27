#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <memory>

#include <alligator/game/game.h>
#include <alligator/game/iscreen.h>
#include <alligator/camera/camera.h>

class MenuScreen;
class MapScreen;

class LD36 : public Game {

public:

	LD36 ( int sw, int sh, bool editor = false );
	virtual ~LD36();

	void create() override ;
	void dispose() override ;
	void update(double delta) override ;

	// all screens
	std::shared_ptr<MenuScreen> m_menuScreen;
	std::shared_ptr<MapScreen> m_mapScreen;

	ALLEGRO_FONT* m_font = nullptr;
	ALLEGRO_FONT* m_fontBig = nullptr;

	Camera::SharedPtr m_camera1;
	Camera::SharedPtr m_camera2;
	Camera::SharedPtr m_camera3;

private:
	bool m_editor;

};

