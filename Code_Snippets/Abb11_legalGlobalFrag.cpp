// mod.cpp
module;

// OK: Präprozessor Anweisung
// Funktionsdeklaration von hello() befindet sich nun im
// globalen Modulfragment
#include "hello.hpp"

export module mod;

void sayHello()
{
    hello();
}
