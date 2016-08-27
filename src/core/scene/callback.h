#pragma once

template <typename T, typename ReturnType, typename... Args>
class Callback
{
public:
	typedef int (T::*TypeMethod)(Args... args);
	Callback(T* object, TypeMethod tm) : m_object(object), m_method(tm) {}
	ReturnType operator()(Args... args) { return ((*m_object).*m_method)(args...); }

private:
	T* m_object;
	TypeMethod m_method;

};

