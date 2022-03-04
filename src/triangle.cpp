#include "main_window.h"

int main(int argc, char const *argv[])
{
	MainWindow window(640, 480, true, false);
	// open a window
	int result = window.open();

	return 0;
}