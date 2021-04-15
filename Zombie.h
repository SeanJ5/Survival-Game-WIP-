#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Entity.h"
#include "Screen.h"

Entity* Zombie_CreateZombieEntity(int x, int y);

void Zombie_Update(Entity* e);
void Zombie_Render( Screen* s, Entity* e );

#endif
