#pragma once

#include "command.h"

class CommandProcessor
{
public:
	virtual ~CommandProcessor();

	virtual void step( const Vec2i& tile ) = 0 ;
	virtual bool tryEnqueueCommand( Command::SharedPtr cmd ) = 0 ;

};

class SingleCommandProcessor : public CommandProcessor
{
public:
	virtual void step( const Vec2i& tile ) override
	{
		if( m_runningCommand != nullptr )
		{
			if( m_runningCommand->status() == Command::Status::Running )
			{
				(*m_runningCommand)(tile);
				if( m_runningCommand->status() == Command::Status::Ready )
				{
					m_runningCommand = nullptr;
				}
			}
		}
	}

	virtual bool tryEnqueueCommand( Command::SharedPtr cmd ) override
	{
		if( m_runningCommand == nullptr || m_runningCommand->status() == Command::Status::Ready )
		{
			m_runningCommand = cmd;
			m_runningCommand->reset();
			return true;
		}
		return false;
	}

private:
	Command::SharedPtr m_runningCommand;

};
