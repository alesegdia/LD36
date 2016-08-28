#pragma once

#include "command.h"
#include "spawner.h"

class EntitySpawnerCommand : public Command
{
public:
	EntitySpawnerCommand( Spawner::SharedPtr spawner, Entity::SharedPtr model_entity )
		: m_spawner(spawner),
		  m_modelEntity(model_entity)
	{

	}

	void delegate( const Vec2i& tile ) override
	{
		m_spawner->spawn(m_modelEntity, tile);
		status( Status::Ready );
	}

	static Entity::SharedPtr MakeEntity( ALLEGRO_BITMAP* bitmap )
	{
		return std::make_shared<Entity>(bitmap, Vec2f(0, 0));
	}

private:
	Spawner::SharedPtr m_spawner;
	Entity::SharedPtr m_modelEntity;

};


class SlimeSpawnerCommand : public EntitySpawnerCommand
{
public:
	SlimeSpawnerCommand( Spawner::SharedPtr spawner ) : EntitySpawnerCommand( spawner,
		MakeEntity(Assets::instance->charactersSheet->getFrame(0, 0)) ) {}
};

class SnakeSpawnerCommand : public EntitySpawnerCommand
{
public:
	SnakeSpawnerCommand( Spawner::SharedPtr spawner ) : EntitySpawnerCommand( spawner,
		MakeEntity(Assets::instance->charactersSheet->getFrame(1, 0)) ) {}
};

class GodSpawnerCommand : public EntitySpawnerCommand
{
public:
	GodSpawnerCommand( Spawner::SharedPtr spawner ) : EntitySpawnerCommand( spawner,
		MakeEntity(Assets::instance->charactersSheet->getFrame(2, 0)) ) {}
};

class DemonSpawnerCommand : public EntitySpawnerCommand
{
public:
	DemonSpawnerCommand( Spawner::SharedPtr spawner ) : EntitySpawnerCommand( spawner,
		MakeEntity(Assets::instance->charactersSheet->getFrame(0, 1)) ) {}
};

class MagnetoballSpawnerCommand : public EntitySpawnerCommand
{
public:
	MagnetoballSpawnerCommand( Spawner::SharedPtr spawner ) : EntitySpawnerCommand( spawner,
		MakeEntity(Assets::instance->charactersSheet->getFrame(1, 1)) ) {}
};

