#include "SimpleStringHdr.h"

int main() {
	SimpleString* test = new SimpleString("Hello World");
	SimpleString* test2 = new SimpleString("Hello World");
	test->concatenate("test");

	test = test2;

	delete(test);
	delete(test2);
	return 0;
}