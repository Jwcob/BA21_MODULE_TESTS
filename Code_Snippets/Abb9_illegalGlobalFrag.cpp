// mod.cpp
module;

// NICHT OK: Ist keine Präprozessor Anweisung!
extern void hello();

export module mod;

void sayHello()
{
    hello(); // NICHT OK: hello() wurde nicht deklariert!
}