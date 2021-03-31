#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "SDL2/SDL.h"
#include "Screen.h"
#include "GameState.h"

SDL_Window* window;         // SDL_Window (the window)
Uint32* pixels;             // Pixel data OF WINDOW
Screen* screen;             // Pixel data OF GAME RASTER
const Uint8 SCALE = 5U;     // Value raster is scaled by to fit window

const Uint8* KeyStates;     // State of every keyboard key

/*========[( Inits graphics )]========*/
void initGraphics()
{
	screen = Screen_Create(160U, 128U);

	SDL_Init(SDL_INIT_VIDEO);
	#define POS SDL_WINDOWPOS_CENTERED

	window = SDL_CreateWindow("Minicraft", POS, POS,
		500,300, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	Bitmaps_CreateAll();
}

/*========[( Free graphics resources )]========*/
void closeGraphics()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	Screen_Destroy(screen);
	Bitmaps_DestroyAll();
}

/*========[( Update game )]========*/
void update()
{
	GameState_Update();
}

/*========[( Render Game )]========*/
void render()
{
	Screen_Clear(screen, 0);

	GameState_Render(screen);

	//SDL_RestoreWindow(window);
	Screen_DrawToWindow(SDL_GetWindowSurface(window), screen);
	SDL_UpdateWindowSurface(window);
}

/*========[( Start game + game loop )]========*/
void run()
{
	srand(time(0));
	initGraphics();

	bool running = true;
	SDL_Event e;

	KeyStates = SDL_GetKeyboardState(NULL);

	/* Init Game */
	GameState_Start();

	#define currentTime (float)clock()/CLOCKS_PER_SEC * 1000

	const float msPerTick = 1000/60.0f;
	double unprocessed = 0;
	float last = currentTime, now;
	int frames, ticks;

	float updateInfo = currentTime;

	while(running)
	{
		now = currentTime;
		unprocessed += (now - last)/msPerTick;
		last = now;

		while (unprocessed >= 1)
		{
				ticks++;
				update();
				while(SDL_PollEvent(&e))
				{
					switch(e.type)
					{
						case SDL_QUIT: running = false; break;
					}
				}

				unprocessed -= 1;
		}
		render();
		frames++;

		if(currentTime - updateInfo > 1000)
		{
				updateInfo += 1000;
				char buf[16];
				snprintf(buf, sizeof buf, "%d ups, %d fps", ticks, frames);
				SDL_SetWindowTitle(window, buf);
				frames = 0;
				ticks = 0;
		}
	}

	/* Close Game */
	GameState_Close();
	closeGraphics();
}

/*========[( public static void main(String args[]) )]========*/
int main(int argc, char* argv[])
{
	run();
}
