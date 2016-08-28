#pragma once

#include <cstdint>
#include <memory>

#include <alligator/util/math.h>

class Command
{
public:
	typedef std::shared_ptr<Command> SharedPtr;

	enum class Status : uint8_t
	{
		Running,
		Ready
	};

	virtual ~Command();

	Status status()
	{
		return m_status;
	}

	Status operator()(const Vec2i& tile)
	{
		delegate(tile);
		return m_status;
	}

	virtual void delegate(const Vec2i& tile) = 0 ;

	virtual void reset()
	{
		m_status = Status::Running;
	}

protected:
	void status( Status new_status )
	{
		m_status = new_status;
	}

private:
	Status m_status = Status::Running;

};
