#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

extern Entity* PLAYER;

Entity* Player_CreatePlayerEntity(int x, int y);
void Player_Update ( Entity* e );
void Player_Render ( Screen* s, Entity* e );

#endif
