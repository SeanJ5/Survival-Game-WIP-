#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "SDL2/SDL.h"
#include "Screen.h"
#include "GameState.h"

SDL_Window* window;         // SDL_Window (the window)
SDL_Renderer* renderer;			// SDL_Renderer (drawing raster to window)
Uint32* pixels;             // Pixel data OF WINDOW
Screen* screen;             // Pixel data OF GAME RASTER
const Uint8 SCALE = 5U;     // Value raster is scaled by to fit window

const Uint8* KeyStates;     // State of every keyboard key

/*========[( Inits graphics )]========*/
void InitGraphics()
{
	// Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Init window
	window = SDL_CreateWindow("Minicraft",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		500,300, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	// Init renderer for drawing to window
	renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_RenderSetLogicalSize(renderer, 224, 126);

	// Init screen struct
	screen = Screen_Create(renderer, 224U, 126U);	// New Screen for game

	// Initialize all Bitmaps (textures) for use
	Bitmaps_CreateAll();
}

/*========[( Free graphics resources )]========*/
void CloseGraphics()
{
	SDL_DestroyWindow(window);	// Destroy the main SDL_Window
	SDL_Quit();					        // Free SDL resources
	Screen_Destroy(screen);		  // Destroy the screen and raster
	Bitmaps_DestroyAll();		    // Free all Bitmaps (textures)
}

/*========[( Update game )]========*/
void Update()
{
	GameState_Update();	// Update main (gameplay) state of game
}

/*========[( Render Game )]========*/
void Render()
{
	Screen_Clear(screen, 0x0);	// Clear screen->raster with a black

	GameState_Render(screen);	// Draw the main (gameplay) state of the game

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	Screen_DrawToWindow(screen, window);
  SDL_RenderPresent(renderer);
}

/*========[( Start game + game loop )]========*/
void Run()
{
	srand(time(0));
	InitGraphics();

	bool running = true;
	SDL_Event e;

	KeyStates = SDL_GetKeyboardState(NULL);

	/* Init Game */
	GameState_Start();

	while(running)
	{
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT: running = false; break;
			}
		}

		Update();
		Render();
	}

	/* Close Game */
	GameState_Close();
	CloseGraphics();
}

/*========[( public static void main(String args[]) )]========*/
int main(int argc, char* argv[])
{
	Run();
}
