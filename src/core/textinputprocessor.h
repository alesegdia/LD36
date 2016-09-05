#pragma once

#include <allegro5/allegro.h>
#include <alligator/input/iinputprocessor.h>

class TextInputProcessor : public IInputProcessor
{
public:
	virtual ~TextInputProcessor()
	{

	}

	// IInputProcessor interface
	void keyUp(int key) override
	{
		if( key == ALLEGRO_KEY_LSHIFT || key == ALLEGRO_KEY_RSHIFT )
		{
			m_mayus = false;
		}
	}

	void keyDown(int key) override
	{
		if( key >= ALLEGRO_KEY_A && key <= ALLEGRO_KEY_Z )
		{
			pushChar( char(key - ALLEGRO_KEY_A) + (m_mayus?'A':'a') );
		}
		if( key >= ALLEGRO_KEY_0 && key <= ALLEGRO_KEY_9 )
		{
			pushChar( char(key - ALLEGRO_KEY_0) + '0' );
		}
		else if( key == ALLEGRO_KEY_SPACE )
		{
			pushChar( ' ' );
		}
		else if( key == ALLEGRO_KEY_BACKSPACE )
		{
			popChar();
		}
		else if( key == ALLEGRO_KEY_LSHIFT || key == ALLEGRO_KEY_RSHIFT )
		{
			m_mayus = true;
		}
	}

	void pushChar( char c )
	{
		if( m_cursor < 128 - 1 )
		{
			m_buffer[m_cursor++] = c;
			m_buffer[m_cursor] = '\0';
		}
	}

	void popChar()
	{
		if( m_cursor > 0 )
		{
			m_buffer[--m_cursor] = '\0';
		}
	}

	const char* str()
	{
		return m_buffer;
	}

private:
	char m_buffer[128];
	size_t m_cursor = 0;
	bool m_mayus = false;

};
