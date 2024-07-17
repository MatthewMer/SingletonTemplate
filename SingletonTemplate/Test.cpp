#include "Test.h"

void Test::Set(int i) {
	this->m_Value = i;
}

int Test::Get() const {
	return this->m_Value;
}