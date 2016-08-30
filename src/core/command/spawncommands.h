#pragma once

#include "command.h"
#include "../scene/spawner.h"

class EntitySpawnerCommand : public Command
{
public:


	EntitySpawnerCommand( Scene::SharedPtr scene, Spawner::SharedPtr spawner, Entity::SharedPtr model_entity, std::string name = "", EntityType et = EntityType::Player )
		: Command(name),
		  m_scene(scene),
		  m_spawner(spawner),
		  m_modelEntity(model_entity),
		  m_entityType(et)
	{

	}

	void delegate( const Vec2i& tile ) override
	{
		if( m_scene->isWalkableTile( tile ) )
		{
			m_spawner->spawn(m_modelEntity, tile, m_entityType);
		}
		status( Status::Ready );
	}

	static Entity::SharedPtr MakeEntity( ALLEGRO_BITMAP* bitmap )
	{
		return std::make_shared<Entity>(bitmap, Vec2f(0, 0));
	}

private:
	Scene::SharedPtr m_scene;
	Spawner::SharedPtr m_spawner;
	Entity::SharedPtr m_modelEntity;
	EntityType m_entityType;

};


class SlimeSpawnerCommand : public EntitySpawnerCommand
{
public:
	SlimeSpawnerCommand( Scene::SharedPtr scene, Spawner::SharedPtr spawner ) :
		EntitySpawnerCommand( scene, spawner, MakeEntity(Assets::instance->charactersSheet->getFrame(0, 0)), "SlimeSpawner" ) {}
};

class SnakeSpawnerCommand : public EntitySpawnerCommand
{
public:
	SnakeSpawnerCommand( Scene::SharedPtr scene, Spawner::SharedPtr spawner ) : EntitySpawnerCommand( scene, spawner,
		MakeEntity(Assets::instance->charactersSheet->getFrame(1, 0)), "SnakeSpawner" ) {}
};

class GodSpawnerCommand : public EntitySpawnerCommand
{
public:
	GodSpawnerCommand( Scene::SharedPtr scene, Spawner::SharedPtr spawner ) : EntitySpawnerCommand( scene, spawner,
		MakeEntity(Assets::instance->charactersSheet->getFrame(2, 0)), "GodSpawner" ) {}
};

class DemonSpawnerCommand : public EntitySpawnerCommand
{
public:
	DemonSpawnerCommand( Scene::SharedPtr scene, Spawner::SharedPtr spawner ) : EntitySpawnerCommand( scene, spawner,
		MakeEntity(Assets::instance->charactersSheet->getFrame(0, 1)), "DemonSpawner" ) {}
};

class MagnetoballSpawnerCommand : public EntitySpawnerCommand
{
public:
	MagnetoballSpawnerCommand( Scene::SharedPtr scene, Spawner::SharedPtr spawner ) : EntitySpawnerCommand( scene, spawner,
		MakeEntity(Assets::instance->charactersSheet->getFrame(1, 1)), "MagnetoballSpawner" ) {}
};

class RemoveEntity : public Command
{
public:
	RemoveEntity( Scene::SharedPtr scene )
		: Command("RemoveEntity"),
		  m_scene(scene)
	{

	}

	void delegate(const Vec2i &tile)
	{
		m_scene->removeEntityAtOrthoTile(tile);
		status( Status::Ready );
	}

private:
	Scene::SharedPtr m_scene;

};

class WallSpawnerCommand : public EntitySpawnerCommand
{
public:
	WallSpawnerCommand( Scene::SharedPtr scene, Spawner::SharedPtr spawner ) :
		EntitySpawnerCommand( scene, spawner, MakeEntity(Assets::instance->objectsSheet->getFrame(0, 1)), "WallSpawner", EntityType::Wall) {}
};
