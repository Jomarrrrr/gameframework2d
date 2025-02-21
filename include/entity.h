#ifndef __ENTITY_H
#define __ENTITY_H

#include "gfc_types.h"
#include "gf2d_sprite.h"


typedef struct Entity_S
{
    Uint8       _inuse;     /**<this is the flag for keeping track of memory usage*/
    Sprite* sprite;     /**<the sprite*/
    float       frame;      /**< current frame of animation for sprite*/
    GFC_Vector2D    position;   /**<where on the screen to draw the thing*/
    GFC_Vector2D	velocity;
    void (*think)(struct Entity_S* self);   /**<function to call do make decisions*/
    void (*update)(struct Entity_S* self);  /**<function to call to execute those decisions*/
    void (*free)(struct Entity_S* self);    /**<clean up any custom allocated data*/
    void* data;                             /**<for ad hoc addition data for the entity*/
}Entity;

void entity_system_initialize(Uint32 max);

/**
 * @brief clean up all active entities
 * @param ignore do not clean up this entity
 */
void entity_clear_all(Entity* ignore);

/**
 * @brief get a blank entity for use
 * @return NULL on no more room or error, a blank entity otherwise
 */
Entity* entity_new();

/**
 * @brief clean up an entity, and free its spot for future use.
 * @param self the entity to free
 */
void entity_free(Entity* self);

/**
 * @brief run the think functions for all active entities
 */
void entity_system_think();

/**
 * @brief run the update functions for all active entities
 */
void entity_system_update();

/**
 * @brief draw all active entities
 */
void entity_system_draw();


#endif