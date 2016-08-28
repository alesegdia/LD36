#pragma once

#include <cstdint>
#include <memory>
#include <string>

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

	Command( std::string name = "" )
		: m_name(name)
	{

	}

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

	const std::string& name()
	{
		return m_name;
	}

protected:
	void status( Status new_status )
	{
		m_status = new_status;
	}

private:
	Status m_status = Status::Running;
	std::string m_name = "";

};
