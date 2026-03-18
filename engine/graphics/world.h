
#pragma once

#include <cglm/cglm.h>
#include "shader_program.h"

typedef unsigned char Voxel;

enum
{
    // Air / Fluids

    VoxelAir = 0,
    VoxelWater,
    VoxelLava,
    VoxelIce,
    VoxelSnow,

    // Natural / Terrain

    VoxelGrass,
    VoxelDirt,
    VoxelPodzol,
    VoxelCoarseDirt,
    VoxelStone,
    VoxelCobblestone,
    VoxelSand,
    VoxelRedSand,
    VoxelGravel,
    VoxelClay,
    VoxelSandstone,
    VoxelRedSandstone,
    VoxelMycelium,
    VoxelMossStone,
    VoxelEndStone,
    VoxelNetherrack,
    VoxelSoulSand,
    VoxelBasalt,
    VoxelBlackstone,
    VoxelObsidian,

    // Ores / Minerals

    VoxelCoal,
    VoxelIron,
    VoxelCopper,
    VoxelGold,
    VoxelDiamond,
    VoxelEmerald,
    VoxelRedstone,
    VoxelLapis,
    VoxelNetherQuartz,
    VoxelNetherGold,
    VoxelAncientDebris,

    // Wood / Plants

    VoxelOakWood,
    VoxelSpruceWood,
    VoxelBirchWood,
    VoxelJungleWood,
    VoxelAcaciaWood,
    VoxelDarkOakWood,
    VoxelOakLeaves,
    VoxelSpruceLeaves,
    VoxelBirchLeaves,
    VoxelJungleLeaves,
    VoxelAcaciaLeaves,
    VoxelDarkOakLeaves,
    VoxelCactus,
    VoxelSugarCane,
    VoxelTallGrass,
    VoxelFern,
    VoxelFlowerRed,
    VoxelFlowerYellow,
    VoxelMushroomRed,
    VoxelMushroomBrown,
    VoxelVine,
    VoxelLilyPad,

    VoxelCount = 128,
};

void WorldCreate();
void WorldDelete();
void WorldDraw(ShaderProgram shaderProgram);

