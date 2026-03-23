
#pragma once

typedef unsigned char Voxel;

enum
{
    // Core
    VoxelAir = 0,
    VoxelGrass,
    VoxelDirt,
    VoxelStone,
    VoxelBedrock,
    VoxelSand,

    // Terrain & Natural
    VoxelGravel,
    VoxelClay,
    VoxelSnow,
    VoxelIce,
    VoxelWater,
    VoxelLava,

    // Stones

    VoxelCobblestone,
    VoxelMossyCobblestone,
    VoxelStoneBricks,
    VoxelGranite,
    VoxelDiorite,
    VoxelAndesite,

    // Ores

    VoxelCoalOre,
    VoxelIronOre,
    VoxelCopperOre,
    VoxelGoldOre,
    VoxelRedstoneOre,
    VoxelLapisOre,
    VoxelDiamondOre,
    VoxelEmeraldOre,

    // Resource Blocks

    VoxelCoalBlock,
    VoxelIronBlock,
    VoxelCopperBlock,
    VoxelGoldBlock,
    VoxelDiamondBlock,
    VoxelEmeraldBlock,

    // Wood

    VoxelOakLog,
    VoxelSpruceLog,
    VoxelBirchLog,
    VoxelJungleLog,
    VoxelAcaciaLog,
    VoxelDarkOakLog,

    // Leaves & Plants

    VoxelOakLeaves,
    VoxelSpruceLeaves,
    VoxelBirchLeaves,
    VoxelJungleLeaves,
    VoxelGrassPlant,
    VoxelCactus,

    // Crops / Nature

    VoxelWheat,
    VoxelPumpkin,
    VoxelMelon,
    VoxelSugarCane,

    // Building

    VoxelPlanks,
    VoxelBricks,
    VoxelGlass,
    VoxelSandstone,
    VoxelSmoothStone,
    VoxelNetherBricks,
    VoxelQuartzBlock,
    VoxelObsidian,

    // Light & Utility

    VoxelTorch,
    VoxelGlowstone,
    VoxelLantern,
    VoxelFurnace,
    VoxelCraftingTable,
    VoxelChest,

    // Special

    VoxelPortal,
    VoxelBarrier
};

extern const unsigned int voxelPropertyTable[64];
