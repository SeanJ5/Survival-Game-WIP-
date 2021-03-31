#include "Screen.h"
#include "string.h"
#include "Bitmaps.h"

int CameraXOffs, CameraYOffs;

Screen* Screen_Create(Uint16 w, Uint16 h)
{
  Screen* s = malloc(sizeof(Screen));
  s->width = w;
  s->height = h;
  s->raster = malloc(w * h * sizeof(Uint32));
  return s;
}

void Screen_Destroy(Screen* s)
{
  free(s->raster);
  free(s);
}

void Screen_DrawToWindow(SDL_Surface* s, Screen* screen)
{
  /*- Used DDA to scale to screen -*/
  int x, xt, xp;
  int y, yt, yp;
  Uint32* pixels = s->pixels;

  for(y = yt = yp = 0; y < s->h; y++)
  {
    for(x = xt = xp = 0; x < s->w; x++)
    {
      pixels[x + y * s->w] = screen->raster[xp + yp * screen->width];
      xt += screen->width;
      if(xt >= s->w)
      {
        xt -= s->w;
        xp++;
      }
    }
    yt += screen->height;
    if(yt >= s->h)
    {
      yt -= s->h;
      yp++;
    }
  }
}

Uint32 Screen_GetRGB(Uint8 r, Uint8 g, Uint8 b)
{
  return ( (r >> 5 << 5) << 16 ) | ( (g >> 5 << 5) << 8) | (b >> 5 << 5);
}

void Screen_FocusCamera(Screen* s, int x, int y)
{
  CameraXOffs = x - s->width / 2;
  CameraYOffs = y - s->height / 2;
}

void Screen_Clear(Screen* s, Uint32 color)
{
  Uint64 size = (Uint64)s->width * s->height;
  for(Uint64 i = 0; i < size; i++)
  {
    s->raster[i] = color;
  }
}

void Screen_BlitBitmap(Screen* s, Bitmap* b, Uint32 colors[3], int xp, int yp, Uint8 flags)
{
  xp -= CameraXOffs;
  yp -= CameraYOffs;

  int x, y;
  Uint32 pixel;

  /* -Start draw positions (inside bitmap, not screen)- */
  const int xs = (xp < 0) * (-xp);
	const int ys = (yp < 0) * (-yp);

  /* -End draw positions (inside bitmap, not screen)- */
	const int xe = b->w - (xp + b->w >= s->width) *
		(xp + b->w - s->width);	// end draw pos (width)
	const int ye = b->h - (yp + b->h >= s->height) *
		(yp + b->h - s->height);	// end draw pos (height)

  for(y = ys; y < ye; y++)
	  for(x = xs; x < xe; x++)
    {
      if((pixel = b->bitmap[x + y * b->w]))
      {
        if((flags & FLIPX) == 0)
          s->raster[(xp + ((xe-xs-1) - x)) + (yp + y) * s->width] = colors[pixel - 1];
        else s->raster[(xp + x) + (yp + y) * s->width] = colors[pixel - 1];
      }

    }
}
