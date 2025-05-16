#include <SDL.h>

#include "simple_logger.h"


#include "gfc_list.h"
#include "gfc_input.h"
#include "gfc_vector.h"

#include "camera.h"
#include "player.h"
#include "slime.h"
#include "air.h"

void player_think(Entity* self);
void player_update(Entity* self);
void player_free(Entity* self);

Entity* player_new()
{
    Entity* self;
    Entity* player;

    self = entity_new();
    player = self;
    if (!self)
    {
        slog("failed to spawn a player entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/main.png",
        128,
        128,
        1,
        0);
    self->frame = 0;
	self->position = gfc_vector2d(100, 100);

    self->think = player_think;
    self->update = player_update;
    self->free = player_free;

  
}
void player_think(Entity* self)
{
    GFC_Vector2D dir = { 0 }; 
    GFC_Vector2D inp = { 0 };
	SDL_Joystick* joystick = SDL_JoystickOpen(0);
    if (SDL_JoystickGetAxis(joystick, 0) < -32700) {
        inp.x -= 1;
        gfc_vector2d_scale(self->velocity, inp, 2);

    }
    if (SDL_JoystickGetAxis(joystick, 0) > 32700) {
        inp.x += 1;
        gfc_vector2d_scale(self->velocity, inp, 2);

    }
    if (SDL_JoystickGetButton(joystick, 0)) {
        inp.y = -1;
        gfc_vector2d_normalize(&inp);
        gfc_vector2d_scale(self->velocity, inp, 10);

    }
    if (gfc_input_command_down("sdown")) {
        self->position = gfc_vector2d(self->position.x, self->position.y + 5);
        gfc_vector2d_normalize(&dir);
        gfc_vector2d_scale(self->velocity, dir, 3);

    }
    
}

void player_update(Entity* self)
{
    if (!self) return;
    self->frame + 0.1;
    if (self->frame >= 16) self->frame = 0;
    gfc_vector2d_add(self->position, self->position, self->velocity);
    if (!self) return;
    if (self->position.y >= 447) self->position.y = 447;
    if (self->position.y <= 0) self->position.y = 0;


    GFC_Vector2D gravity = gfc_vector2d(0, 1);

    gfc_vector2d_add(self->velocity, self->velocity, gravity);
    gfc_vector2d_add(self->position, self->position, self->velocity);
    gfc_vector2d_normalize(&self->velocity);
 
    
}

void player_free(Entity* self)
{
    if (self) return;
}

GFC_Vector2D get_player(Entity* player)
{
	GFC_Vector2D position;
	
	if (!player) return gfc_vector2d(0, 0);
	position = player->position;
	return position;
}

/*eol@eof*/