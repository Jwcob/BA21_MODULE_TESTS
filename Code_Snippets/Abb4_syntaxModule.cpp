// mod.cpp
module; // global-module-fragment (opt)

#define foo "World"

export module mod; // module-declaration

import <iostream>; // module-import-declaration (opt)

export void sayHello(); // export-declaration (opt)

module:private; // private-module-fragment Start (opt)

// declaration-seq Start
void sayHello()
{
    std::cout << "Hello " << foo << std::endl;
}
// declaration-seq Ende
