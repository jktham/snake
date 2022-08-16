#include <iostream>

#include "app.h"
#include "game.h"
#include "global.h"

int main()
{	
	app.setup();
	app.mainloop();
	app.cleanup();
}
