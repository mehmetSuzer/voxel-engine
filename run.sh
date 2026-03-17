
if [[ ! -d build ]]
then
    ./build.sh
fi

if [ -f build/voxel-engine ]
then
    ./build/voxel-engine
fi

