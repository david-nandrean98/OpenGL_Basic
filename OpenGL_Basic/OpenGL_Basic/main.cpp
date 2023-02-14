#include <iostream>
#include "ApplicationWindow.h"

int main()
{
	glfwutils::ApplicationWindow appWin(1000, 1000, "Demo");
	appWin.Run();
	return 0;
}