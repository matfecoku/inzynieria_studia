#include <iostream>
#include "Application.h"

int main() {

	std::cout << "Poczatek aplikacji.\n\n";

	Application app;
	app.run();

	std::cout << "\nKoniec aplikacji.\n";
	return 0;
}