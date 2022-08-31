#include <iostream>
#include "ApplicationWindow.h"

int main()
{
	glfwutils::ApplicationWindow appWin(800, 800, "Demo");
	appWin.Run();
	return 0;
}