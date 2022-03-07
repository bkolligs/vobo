#include "sandbox.h"

template<typename ...Args>
void logDebug(Args && ...args) {
	(std::cout << ... << args);
}

int main(int argc, char const *argv[])
{
	vobo::MainWindow window(1200, 900, true, false);
	int result = window.open();

	return 0;
}