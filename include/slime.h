#ifndef __SLIME_H__
#define __SLIME_H__

#include "entity.h"
#include "gfc_shape.h"

/**
 * @brief slime companion
 * @return NULL on error, or a pointer to the player otherwise
 */
Entity* slime_new();

#endif