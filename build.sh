
if [[ "$1" == "--all" && -d build ]]
then
    rm -rf build
fi

cmake -S . -B build 
# -DCMAKE_BUILD_TYPE=Release

cmake --build build -j${nproc}

