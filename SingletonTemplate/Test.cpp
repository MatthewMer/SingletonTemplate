#include "Test.h"

void Test::Set(const int& i) {
	this->m_Value = i;
}

int Test::Get() const {
	return this->m_Value;
}