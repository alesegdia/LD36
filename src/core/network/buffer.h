#pragma once

#include <cstdint>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>

class Buffer
{
public:
	static constexpr size_t Size = 128;

	typedef Buffer* Ptr;

	Buffer()
	{
		memset(m_data, 0, Size);
	}

	uint8_t& operator[]( size_t index )
	{
		assert( index >= 0 && index < Size );
		return m_data[index];
	}

	template<typename T>
	bool append( T datum )
	{
		if( m_cursor + sizeof(T) < Buffer::Size )
		{
			*reinterpret_cast<T*>(&m_data[m_cursor]) = datum;
			m_cursor += sizeof(T);
			m_size = std::max( m_size, m_cursor + sizeof(T) );
			return true;
		}
		return false;
	}

	void resetCursor()
	{
		m_cursor = 0;
	}

	size_t size()
	{
		return m_size;
	}

	void* data()
	{
		return static_cast<void*>(m_data);
	}

private:
	uint8_t m_data[Size];
	size_t m_size = 0;
	size_t m_cursor = 0;

};

