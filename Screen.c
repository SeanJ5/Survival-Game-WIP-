#include "Screen.h"
#include "string.h"
#include "Bitmaps.h"

/*====[( USED BY ENTIRE GAME FOR CAMERA OFFSETS )]====*/
int CameraXOffs, CameraYOffs;

/*====[( CREATE SCREEN STRUCT ON HEAP )]====*/
Screen* Screen_Create ( SDL_Renderer* r, Uint16 w, Uint16 h )
{
  Uint32 rMask, gMask, bMask, aMask;

  if (SDL_BYTEORDER == SDL_LIL_ENDIAN)
  {
    rMask = 0xFF000000;
    gMask = 0x00FF0000;
    bMask = 0x0000FF00;
    aMask = 0x000000FF;
  }
  else
  {
    rMask = 0x000000FF;
    gMask = 0x0000FF00;
    bMask = 0x00FF0000;
    aMask = 0xFF000000;
  }

  Screen* s = malloc ( sizeof ( Screen ) );
  s->width = w;
  s->height = h;
  s->surface = SDL_CreateRGBSurface ( 0, w, h, 32,
          rMask, gMask, bMask, aMask);
  s->renderer = r;
  s->raster = s->surface->pixels;
  return s;
}

/*====[( FREE MEMORY USED BY SCREEN )]====*/
void Screen_Destroy ( Screen* s )
{
  SDL_FreeSurface (s->surface);
  free (s);
}

/*============================[( Screen_DrawToWindow )]============================*/
void Screen_DrawToWindow(Screen* screen, SDL_Window* window)
{
  SDL_Rect screenRect;
  
  screen->texture = SDL_CreateTextureFromSurface(screen->renderer, screen->surface);
  SDL_RenderCopy(screen->renderer, screen->texture, NULL, NULL);
  SDL_RenderPresent(screen->renderer);
  SDL_DestroyTexture(screen->texture);
}

/*====[( RETURN CLOSED RGB VALUE IN REDUCED PALETTE )]====*/
Uint32 Screen_GetRGB(Uint8 r, Uint8 g, Uint8 b)
{
  return (( (r >> 5 << 5) << 24 ) | ( (g >> 5 << 5) << 16) | ((b >> 5 << 5) << 8) | 255);
}

/*====[( SET CAMERA OFFSETS ACCORDING x, y )]====*/
void Screen_FocusCamera(Screen* s, int x, int y)
{
  CameraXOffs = x - s->width / 2;
  CameraYOffs = y - s->height / 2;
}

/*====[( CLEAR Screen->raster WITH color )]====*/
void Screen_Clear(Screen* s, Uint32 color)
{
  Uint64 size = (Uint64)s->width * s->height;
  for(Uint64 i = 0; i < size; i++)
  {
    s->raster[i] = color;
  }
}

/*====[( BLIT BITMAP TO Screen->raster WIDTH FLAGS (FLIPPED ON X OR Y, ETC.) )]====*/
void Screen_BlitBitmap(Screen* s, Bitmap* b, Uint32 colors[3], int xp, int yp, Uint8 flags)
{
  xp -= CameraXOffs;
  yp -= CameraYOffs;

  int x, y;
  int xdraw, ydraw;
  bool flipx = flags & FLIPX;
  bool flipy = flags & FLIPY;
  Uint32 pixel;

  /* -Start draw positions (inside bitmap, not screen)- */
  const int xs = (xp < 0) * (-xp);
  const int ys = (yp < 0) * (-yp);

  /* -End draw positions (inside bitmap, not screen)- */
  const int xe = b->w - (xp + b->w >= s->width) *
	(xp + b->w - s->width);  // end draw pos (width)
  const int ye = b->h - (yp + b->h >= s->height) *
	(yp + b->h - s->height); // end draw pos (height)

  for(y = ys; y < ye; y++)
	  for(x = xs; x < xe; x++)
    {
      if((pixel = b->bitmap[x + y * b->w]))
      {
        s->raster[(xp + x) + (yp + y) * s->width] = colors[pixel - 1];
      }
    }
}
