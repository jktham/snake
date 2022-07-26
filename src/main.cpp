#include <iostream>

#include "app.h"
#include "global.h"

int main()
{	
	app.initialize();
	app.mainloop();
	app.cleanup();
}
