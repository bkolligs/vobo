#include "sandbox.h"
#include <filesystem>

int main(int argc, char const *argv[])
{
	std::filesystem::path voboPath = "/";
	vobo::MainWindow window(1200, 900, true, true);
	int result = window.open();

	return 0;
}