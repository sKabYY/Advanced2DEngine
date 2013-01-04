#include <iostream>
#include "../../Engine/Advanced2D.h"

bool game_preload() {
	g_engine->message(g_engine->getVersionText(), "TEST ENGINE");
	return false;
}

bool game_init(HWND hWnd) {return 0;}
void game_update() {}
void game_end() {}
