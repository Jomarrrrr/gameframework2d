#include "simple_logger.h"

#include "gfc_list.h"
#include "gfc_input.h"

#include "slime.h"
#include "air.h"

void slime_update(Entity* self);
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


    self->frame = 0;

    self->update = slime_update;
    self->free = slime_free;
}

void slime_update(Entity* self)
{
    if (!self) return;
    self->velocity = gfc_vector2d(0, 0);
    if (gfc_input_command_down("sright")) {
        self->velocity.x += 1;
        
    }
    if (gfc_input_command_down("sleft")) {
        self->velocity.x -= 1;
   
    }
    if (gfc_input_command_down("sup")) {
        self->velocity.y -= 1;
       
    }
    if (gfc_input_command_down("sdown")) {
        self->velocity.y += 1;

    }
    if (gfc_input_command_down("jump")) {
       air_new();

    }
    if (gfc_input_command_down("kill")) {
        entity_free(self);
    }
    if (!self) return;
    self->frame + 0.1;
    if (self->frame >= 16) self->frame = 0;
    gfc_vector2d_normalize(&self->velocity);
    gfc_vector2d_add(self->position, self->position, self->velocity);

}

void slime_free(Entity* self)
{
    if(!self) return;
    free(self);
    
}

/*eol@eof*/ 