#include "sandbox.h"

using namespace vobo;

int add(int first, int second) {
	return first + second;
}
int main(int argc, char const *argv[])
{
	Window window(800, 800, true, true);
	int result = window.open();
	glm::mat4 test = glm::mat4(1.0f);

	return 0;
}