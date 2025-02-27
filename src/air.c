#include <stdio.h>


#include "simple_logger.h"

#include "gfc_list.h"
#include "gfc_input.h"

#include "slime.h"
#include "air.h"
float life = 1;
void air_update(Entity* self);
void air_free(Entity* self);
Entity* air_new() {
	Entity* self;
	self = entity_new();
	if (!self) {
		slog("failed to spawn air");
		return NULL;
	}
	 life = 1;


	// start sprite
	self->sprite = gf2d_sprite_load_all(
		"images/rat.png", 128, 110, 1, 0);

	self->frame = 0;
	
	
	self->update = air_update;

	
	
}

void air_update(Entity* self) {
	if (!self) return;
	
	self->velocity.x = 20;
	
	
	
		life += 1;
		if (life > 1500) {
			entity_free(self);
			
		
			return;


		}
		gfc_vector2d_add(self->position, self->position, self->velocity);
		return self;

	
}
void air_free(Entity* self)
{
	if (!self) return;
	free(self);

}







/*eol@eof*/