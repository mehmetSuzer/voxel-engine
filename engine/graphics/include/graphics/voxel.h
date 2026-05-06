
#pragma once

typedef unsigned char Voxel;

enum
{
    // Core

    VoxelAir     = 0,
    VoxelGrass   = 1,
    VoxelDirt    = 2,
    VoxelStone   = 3,
    VoxelBedrock = 4,
    VoxelSand    = 5,

    // Terrain & Natural

    VoxelGravel =  6,
    VoxelClay   =  7,
    VoxelSnow   =  8,
    VoxelIce    =  9,
    VoxelWater  = 10,
    VoxelLava   = 11,

    // Stones

    VoxelCobblestone      = 12,
    VoxelMossyCobblestone = 13,
    VoxelStoneBricks      = 14,
    VoxelGranite          = 15,
    VoxelDiorite          = 16,
    VoxelAndesite         = 17,

    // Ores

    VoxelCoalOre     = 18,
    VoxelIronOre     = 19,
    VoxelCopperOre   = 20,
    VoxelGoldOre     = 21,
    VoxelRedstoneOre = 22,
    VoxelLapisOre    = 23,
    VoxelDiamondOre  = 24,
    VoxelEmeraldOre  = 25,

    // Resource Blocks

    VoxelCoalBlock    = 26,
    VoxelIronBlock    = 27,
    VoxelCopperBlock  = 28,
    VoxelGoldBlock    = 29,
    VoxelDiamondBlock = 30,
    VoxelEmeraldBlock = 31,

    // Wood

    VoxelOakLog     = 32,
    VoxelSpruceLog  = 33,
    VoxelBirchLog   = 34,
    VoxelJungleLog  = 35,
    VoxelAcaciaLog  = 36,
    VoxelDarkOakLog = 37,

    // Leaves & Plants

    VoxelOakLeaves    = 38,
    VoxelSpruceLeaves = 39,
    VoxelBirchLeaves  = 40,
    VoxelJungleLeaves = 41,
    VoxelGrassPlant   = 42,
    VoxelCactus       = 43,

    // Crops / Nature

    VoxelWheat     = 44,
    VoxelPumpkin   = 45,
    VoxelMelon     = 46,
    VoxelSugarCane = 47,

    // Building

    VoxelPlanks       = 48,
    VoxelBricks       = 49,
    VoxelGlass        = 50,
    VoxelSandstone    = 51,
    VoxelSmoothStone  = 52,
    VoxelNetherBricks = 53,
    VoxelQuartzBlock  = 54,
    VoxelObsidian     = 55,

    // Light & Utility

    VoxelTorch         = 56,
    VoxelGlowstone     = 57,
    VoxelLantern       = 58,
    VoxelFurnace       = 59,
    VoxelCraftingTable = 60,
    VoxelChest,

    // Special

    VoxelPortal  = 61,
    VoxelBarrier = 62,

    VoxelCount,
};

extern const unsigned int voxelPropertyTable[64];

