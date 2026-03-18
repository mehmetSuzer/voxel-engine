
#pragma once

#include <cglm/cglm.h>
#include "shader_program.h"

typedef unsigned char Voxel;

#define VOXEL_AIR     ((Voxel)0)
#define VOXEL_BLACK   ((Voxel)1)
#define VOXEL_RED     ((Voxel)2)
#define VOXEL_GREEN   ((Voxel)3)
#define VOXEL_BLUE    ((Voxel)4)
#define VOXEL_YELLOW  ((Voxel)5)
#define VOXEL_MAGENTA ((Voxel)6)
#define VOXEL_CYAN    ((Voxel)7)
#define VOXEL_WHITE   ((Voxel)8)

void WorldCreate();
void WorldDelete();
void WorldDraw(ShaderProgram shaderProgram);

