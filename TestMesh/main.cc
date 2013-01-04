#include "../../Engine/Advanced2D.h"
#include <vector>

using namespace Advanced2D;

#define KEY_DOWN(vk) ((GetAsyncKeyState(vk) & 0x8000)?1:0)

Camera *camera;
#define SPHERES 100

typedef std::vector<Mesh*>::iterator iter;
std::vector<Mesh*> entities;

bool game_preload() {
	g_engine->setAppTitle("BOUNCING BALLS");
	g_engine->setFullscreen(false);
	g_engine->setScreenWidth(1024);
	g_engine->setScreenHeight(768);
	g_engine->setColorDepth(32);
	return true;
}

bool game_init(HWND hWnd) {
	srand(time(NULL));
	camera = new Camera();
	camera->setPosition(0.0f, 2.0f, 6.0f);
	camera->setTarget(0.0f, 0.0f, 0.0f);
	camera->Update();

	Mesh *ball;
	for (int n = 0; n < SPHERES; ++n) {
		ball = new Mesh();
		ball->Load("ball.x");
		ball->SetScale(0.3f, 0.3f, 0.3f);
		float x = (float)(rand()%80+1) / 10000.0f;
		float y = (float)(rand()%80+1) / 10000.0f;
		float z = (float)(rand()%80+1) / 10000.0f;
		ball->SetPosition(0.0f, 0.0f, 0.0f);
		ball->SetVelocity(x, y, z);
		ball->SetRotation(0.1f, 0.2f, 0.01f);
		entities.push_back(ball);
	}
	return true;
}

void game_update() {
	for (iter i = entities.begin(); i != entities.end(); ++i) {
		(*i)->Update();
		(*i)->LimitBoundary(-5, 5, 4, -4, 4, -4);
	}
	if (KEY_DOWN(VK_ESCAPE)) g_engine->Close();
}

void game_end() {
	delete camera;
	for (iter i = entities.begin(); i != entities.end(); ++i) {
		delete *i;
	}
	entities.clear();
}

void game_render3d() {
	static DWORD start = 0;
	g_engine->ClearScene(D3DCOLOR_RGBA(30, 30, 100, 0));
	g_engine->SetIdentity();
	for (iter i = entities.begin(); i != entities.end(); ++i) {
		(*i)->Transform();
		(*i)->Draw();
	}
}
