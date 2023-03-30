#ifndef AVALON_INTERNAL_H
#define AVALON_INTERNAL_H

#include "avalon.h"



extern avalon_list meshes;
extern uint shader_flat;


typedef struct {
	uint64_t location;
	char title[56];
} avalon_uniform;


#endif
