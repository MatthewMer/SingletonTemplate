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

    i = 3;
    sp->Set(i);
    cout << "Value set to: " << i << endl;
    cout << "Shared pointer: " << sp->Get() << endl;
    cout << "Weak pointer: " << wp.lock()->Get() << endl;

    cout << endl;
    cout << "Number of owners: " << sp.use_count() << endl;

    cout << endl;
    cout << "Is constructible? "        << std::is_constructible<Test>::value       << endl;
    cout << "Is destructible? "         << std::is_destructible<Test>::value        << endl;
    cout << "Is move assignable? "      << std::is_move_assignable<Test>::value     << endl;
    cout << "Is move constructible? "   << std::is_move_constructible<Test>::value  << endl;
    cout << "Is copy assignable? "      << std::is_copy_assignable<Test>::value     << endl;
    cout << "Is copy constructible? "   << std::is_copy_constructible<Test>::value  << endl;
}