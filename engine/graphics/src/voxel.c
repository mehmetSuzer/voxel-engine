
#include "graphics/voxel.h"

#define VOXEL_SOLID        (1u << 0)
#define VOXEL_TRANSPARENT  (1u << 1)
#define VOXEL_FLAMMABLE    (1u << 2)

#define VOXEL_BREAK_SHIFT  3

#define VOXEL_MAKE(solid, transparent, flammable, breakTime) \
    ((solid       ? VOXEL_SOLID       : 0u)    |             \
     (transparent ? VOXEL_TRANSPARENT : 0u)    |             \
     (flammable   ? VOXEL_FLAMMABLE   : 0u)    |             \
     ((breakTime & 31u) << VOXEL_BREAK_SHIFT))

const unsigned int voxelPropertyTable[64] = {
    [VoxelAir]              = VOXEL_MAKE(0,1,0,0),
    [VoxelGrass]            = VOXEL_MAKE(1,0,1,2),
    [VoxelDirt]             = VOXEL_MAKE(1,0,0,2),
    [VoxelStone]            = VOXEL_MAKE(1,0,0,5),
    [VoxelBedrock]          = VOXEL_MAKE(1,0,0,9),
    [VoxelSand]             = VOXEL_MAKE(1,0,0,2),
    [VoxelGravel]           = VOXEL_MAKE(1,0,0,2),
    [VoxelClay]             = VOXEL_MAKE(1,0,0,3),
    [VoxelSnow]             = VOXEL_MAKE(1,1,0,1),
    [VoxelIce]              = VOXEL_MAKE(1,1,0,2),
    [VoxelWater]            = VOXEL_MAKE(0,1,0,0),
    [VoxelLava]             = VOXEL_MAKE(0,1,0,0),
    [VoxelCobblestone]      = VOXEL_MAKE(1,0,0,4),
    [VoxelMossyCobblestone] = VOXEL_MAKE(1,0,0,4),
    [VoxelStoneBricks]      = VOXEL_MAKE(1,0,0,4),
    [VoxelGranite]          = VOXEL_MAKE(1,0,0,4),
    [VoxelDiorite]          = VOXEL_MAKE(1,0,0,4),
    [VoxelAndesite]         = VOXEL_MAKE(1,0,0,4),
    [VoxelCoalOre]          = VOXEL_MAKE(1,0,0,4),
    [VoxelIronOre]          = VOXEL_MAKE(1,0,0,4),
    [VoxelCopperOre]        = VOXEL_MAKE(1,0,0,4),
    [VoxelGoldOre]          = VOXEL_MAKE(1,0,0,4),
    [VoxelRedstoneOre]      = VOXEL_MAKE(1,0,0,4),
    [VoxelLapisOre]         = VOXEL_MAKE(1,0,0,4),
    [VoxelDiamondOre]       = VOXEL_MAKE(1,0,0,5),
    [VoxelEmeraldOre]       = VOXEL_MAKE(1,0,0,5),
    [VoxelCoalBlock]        = VOXEL_MAKE(1,0,0,5),
    [VoxelIronBlock]        = VOXEL_MAKE(1,0,0,6),
    [VoxelCopperBlock]      = VOXEL_MAKE(1,0,0,5),
    [VoxelGoldBlock]        = VOXEL_MAKE(1,0,0,6),
    [VoxelDiamondBlock]     = VOXEL_MAKE(1,0,0,7),
    [VoxelEmeraldBlock]     = VOXEL_MAKE(1,0,0,7),
    [VoxelOakLog]           = VOXEL_MAKE(1,0,1,3),
    [VoxelSpruceLog]        = VOXEL_MAKE(1,0,1,3),
    [VoxelBirchLog]         = VOXEL_MAKE(1,0,1,3),
    [VoxelJungleLog]        = VOXEL_MAKE(1,0,1,3),
    [VoxelAcaciaLog]        = VOXEL_MAKE(1,0,1,3),
    [VoxelDarkOakLog]       = VOXEL_MAKE(1,0,1,3),
    [VoxelOakLeaves]        = VOXEL_MAKE(1,1,1,1),
    [VoxelSpruceLeaves]     = VOXEL_MAKE(1,1,1,1),
    [VoxelBirchLeaves]      = VOXEL_MAKE(1,1,1,1),
    [VoxelJungleLeaves]     = VOXEL_MAKE(1,1,1,1),
    [VoxelGrassPlant]       = VOXEL_MAKE(0,1,1,1),
    [VoxelCactus]           = VOXEL_MAKE(1,0,1,2),
    [VoxelWheat]            = VOXEL_MAKE(0,1,1,1),
    [VoxelPumpkin]          = VOXEL_MAKE(1,0,1,2),
    [VoxelMelon]            = VOXEL_MAKE(1,0,1,2),
    [VoxelSugarCane]        = VOXEL_MAKE(0,1,1,1),
    [VoxelPlanks]           = VOXEL_MAKE(1,0,1,2),
    [VoxelBricks]           = VOXEL_MAKE(1,0,0,4),
    [VoxelGlass]            = VOXEL_MAKE(1,1,0,1),
    [VoxelSandstone]        = VOXEL_MAKE(1,0,0,3),
    [VoxelSmoothStone]      = VOXEL_MAKE(1,0,0,4),
    [VoxelNetherBricks]     = VOXEL_MAKE(1,0,0,4),
    [VoxelQuartzBlock]      = VOXEL_MAKE(1,0,0,3),
    [VoxelObsidian]         = VOXEL_MAKE(1,0,0,9),
    [VoxelTorch]            = VOXEL_MAKE(0,1,1,1),
    [VoxelGlowstone]        = VOXEL_MAKE(1,0,0,2),
    [VoxelLantern]          = VOXEL_MAKE(1,1,0,2),
    [VoxelFurnace]          = VOXEL_MAKE(1,0,0,4),
    [VoxelCraftingTable]    = VOXEL_MAKE(1,0,1,2),
    [VoxelChest]            = VOXEL_MAKE(1,0,1,2),
    [VoxelPortal]           = VOXEL_MAKE(0,1,0,0),
    [VoxelBarrier]          = VOXEL_MAKE(1,1,0,9),
};

