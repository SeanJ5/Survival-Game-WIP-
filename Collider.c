#include "Collider.h"

Collider* Collider_Create(int x, int y, Uint8 w, Uint8 h)
{
  Collider* c = malloc(sizeof(Collider));
  c->x = x; c->y = y;
  c->w = w; c->h = h;
  return c;
}

void Collider_Destroy(Collider* c)
{
  free(c);
}
