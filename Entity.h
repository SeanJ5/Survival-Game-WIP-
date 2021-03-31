#pragma once

#include "Bitmaps.h"
#include "Collider.h"
#include "Screen.h"
#include "Level.h"
#include "Tiles.h"

typedef struct
{
  Bitmap* image;
  Collider* collider;
  Uint32 colors[3];
  void (*update);
  void (*render)(Screen* s);
  signed char renderXOffs;
  signed char renderYOffs;
} Entity;

Entity* Entity_Create(int x, int y, Uint8 w, Uint8 h,
                      Bitmap* image, Uint32 colors[3]);
void Entity_Destroy(Entity* e);

void Entity_Move(Level* l, Entity* e, int xa, int ya);

void Entity_Render(Screen* s, Entity* e, Uint8 flags);
