// SingletonTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Test.h"

using std::cout, std::endl;

int main()
{
    auto sp = Test::s_GetInstance();
    std::weak_ptr<Test> wp = sp;
    cout << "Instance created" << endl;

    int i = 5;
    sp->Set(i);
    cout << "Value set to: " << i << endl;
    cout << "Shared pointer: " << sp->Get() << endl;
    cout << "Weak pointer: " << wp.lock()->Get() << endl;

    Test::s_ResetInstance();
    cout << "Instance resetted (set to 0)" << endl;
    cout << "Shared pointer: " << sp->Get() << endl;
    cout << "Weak pointer: " << wp.lock()->Get() << endl;
}