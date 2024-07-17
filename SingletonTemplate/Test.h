#pragma once
#include "Singleton.h"

/* *****************************************************************
	Simply inherit publicly from Singleton with class as 
	template parameter, make constructor etc. private 
	and make Singleton<T> friend class (ctor access)
***************************************************************** */

class Test : public Singleton<Test> {
public:
	void Set(int i);
	int Get() const;

private:
	friend class Singleton<Test>;
	Test() = default;

	int m_Value = 0;
};

