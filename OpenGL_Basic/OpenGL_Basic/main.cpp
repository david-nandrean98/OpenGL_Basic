#include <iostream>
#include "ApplicationWindow.h"

int main()
{
	glfwutils::ApplicationWindow appWin(1920, 1080, "Demo");
	appWin.Run();
	return 0;
}