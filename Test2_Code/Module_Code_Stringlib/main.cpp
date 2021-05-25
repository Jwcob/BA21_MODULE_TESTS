import SimpleStringMod;

int main() {
	SimpleStringMod* test = new SimpleStringMod("Hello World");
	SimpleStringMod* test2 = new SimpleStringMod("Hello World");
	test->concatenate("test");
	
	test = test2;

	delete(test);
	delete(test2);
	return 0;
}