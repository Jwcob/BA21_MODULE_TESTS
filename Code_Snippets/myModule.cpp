export module myModule;
import <iostream>;

std::string world()
{
 return "World!";
}

export void foo()
{
 std::cout << "Hello " << world() << std::endl;
}
