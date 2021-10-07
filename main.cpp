#include "Universe.h"

int main() {

	Universe app;
	app.showFPS(false);
	app.setMaxFPS(60);
	app.run();

	return 0;
}
