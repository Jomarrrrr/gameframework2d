#include <SDL.h>

#include "simple_logger.h"

#include "gfc_list.h"
#include "gfc_input.h"
#include "gfc_audio.h"

#include "camera.h"
#include "player.h"
#include "slime.h"
#include "air.h"
#include "world.h"



void slime_update(Entity* self);
void slime_think(Entity* self);
void slime_free(Entity* self);

Entity* slime_new()
{
    Entity* self;
    

    self = entity_new();
    if (!self)
    {
        slog("failed to spawn a player entity");
        return NULL;
    }
    self->sprite = gf2d_sprite_load_all(
        "images/slime.png",
        128,
        128,
        1,
        0);
    self->offset.y = 0;
    self->offset.x = 0;

    self->bounds = gfc_rect(self->offset.x+self->position.x, self->position.y, self->position.x + 128, self->position.y + 128);
    self->frame = 0;
    self->position = gfc_vector2d(100, 100);
    self->update = slime_update;
    self->think = slime_think;
    self->free = slime_free;
   
}

void slime_think(Entity* self)
{


    if (!self) return;
    GFC_Vector2D inp = { 0 };
    int mx = 0, my = 0;
    SDL_Joystick* joystick = SDL_JoystickOpen(1);
    GFC_Sound* sfx = gfc_sound_load("audio/tele.wav", .5, 0);


    if (gfc_input_command_down("sright")) {
        inp.x += 1;
        gfc_vector2d_scale(self->velocity, inp, 2);

    }
    if (gfc_input_command_down("sleft")) {
        inp.x -= 1;
        gfc_vector2d_scale(self->velocity, inp, 2);

    }
    if (gfc_input_command_down("sup")) {
        inp.y = -1;
        gfc_vector2d_normalize(&inp);
        gfc_vector2d_scale(self->velocity, inp, 10);
       
    }
    if (gfc_input_command_down("sdown")) {
        self->position = gfc_vector2d(self->position.x, self->position.y + 5);

    }
    if (gfc_input_command_down("jump")) {
        self->position = gfc_vector2d(self->position.x, self->position.y -50);

    }
    if (gfc_input_command_down("dleft")) {
        inp.x -= 1;
        gfc_vector2d_scale(self->velocity, inp, 8);

    }
    if (gfc_input_command_down("dright")) {
        inp.x += 1;
        gfc_vector2d_scale(self->velocity, inp, 8);
    }
    if (gfc_input_command_down("air")) {
        air_new();
    }
    if (gfc_input_command_down("kill")) {
        SDL_GetMouseState(&mx, &my);
        self->position.x = mx;
        self->position.y = my;
        gfc_sound_play(sfx, 0, 1, -1, -1);
    }
    if (!self) return;
    self->frame + 0.1;
    if (self->frame >= 16) self->frame = 0;
  


    self->bounds = gfc_rect(self->position.x, self->position.y, 128, 128);

}
void slime_update(Entity* self) {
    if (!self) return;
    if (self->position.y >= 447) self->position.y = 447; 
	if (self->position.y <= 0) self->position.y = 0;
   

    GFC_Vector2D gravity = gfc_vector2d(0, 1);

    gfc_vector2d_add(self->velocity, self->velocity, gravity);
    gfc_vector2d_add(self->position, self->position, self->velocity);
    gfc_vector2d_normalize(&self->velocity);
    
    camera_center_on(self->position);


}

void slime_free(Entity* self)
{
    if(!self) return;
    entity_free(self);
    
}

/*eol@eof*/ 