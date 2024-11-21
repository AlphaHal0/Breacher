//#include <iostream>
//#include <raylib.h>
//#include <raylib-cpp.hpp>
//#include <raylib.hpp>
#include <raylib.h>

#include <string>
#include <cmath>
// Constants
const char* GAME_VERSION = "Breacher v0.0.1:a - Indev";
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int FPS = 240;


class Player {
public:
	float X = 500.0f;
	float Y = 200.0f;

	int size = 20;

	int health = 100;
	float speed = 2.0f;

	void render() const {
		DrawCircle(static_cast<int>(X), static_cast<int>(Y), size, RED);
	}

	void handleInput(Player& player) {
		//TODO: Background follows player with degree of freedom

		if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.X += player.speed;
		if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.X -= player.speed;
		if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) player.Y -= player.speed;
		if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) player.Y += player.speed;
	}

	void boundRestrictions(Player& player) {
		if (player.X >= SCREEN_WIDTH) {
			player.X = SCREEN_WIDTH;
		}
		if (player.X <= 0) {
			player.X = 0;
		}
		if (player.Y >= SCREEN_HEIGHT) {
			player.Y = SCREEN_HEIGHT;
		}
		if (player.Y <= 0) {
			player.Y = 0;
		}
	}

};


class Weapon {
public:
	int nuzzleVelocity = 0;
	int mass = 0;
	int damageMalt = 1;

	int calculateDamage() const {
		return (1 / 2 * mass) * pow(nuzzleVelocity, 2) * damageMalt;
	}


};

class Debug {
public:
	bool screenboundary = true;

	bool showFPS = true;


	void DebugRendering() {
		if (screenboundary == true) {
			DrawRectangleLines(1, 1, SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2, GREEN);
		}

		if (showFPS == true) {
			DrawFPS(5, 5);
		}

	}
};




int main() {
	Player player;
	Debug debug;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_VERSION);

	SetTargetFPS(FPS);


	Image image = LoadImage("background.png");
	ImageResize(&image, 1920 + 100, 1080 + 100); // 100 for buffer
	Texture2D texture = LoadTextureFromImage(image);

	while (!WindowShouldClose()) {

		// Update
		//----------------------------------------------------------------------------------
		player.handleInput(player);
		player.boundRestrictions(player);
		//----------------------------------------------------------------------------------


		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		debug.DebugRendering();

		ClearBackground(RAYWHITE);


		DrawTexture(texture, SCREEN_WIDTH / 2 - image.width / 2, SCREEN_HEIGHT / 2 - image.height / 2, WHITE);

		player.render(); // Render red circ UwU

		DrawText("Henry is a monkey", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	CloseWindow();
	return 0;
}