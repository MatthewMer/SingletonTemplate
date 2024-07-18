#pragma once
#include "Singleton.h"

/* *****************************************************************
	Simply inherit publicly from Singleton with class as 
	template parameter
***************************************************************** */

class Test : public Singleton<Test> {
public:
	void Set(const int& i);
	int Get() const;

private:
	int m_Value = 0;
};

